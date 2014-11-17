/*--------------------------------------------------------------------
  (C) Copyright 2006-2011 Barcelona Supercomputing Center 
                          Centro Nacional de Supercomputacion
  
  This file is part of Mercurium C/C++ source-to-source compiler.
  
  See AUTHORS file in the top level directory for information 
  regarding developers and contributors.
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3 of the License, or (at your option) any later version.
  
  Mercurium C/C++ source-to-source compiler is distributed in the hope
  that it will be useful, but WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the GNU Lesser General Public License for more
  details.
  
  You should have received a copy of the GNU Lesser General Public
  License along with Mercurium C/C++ source-to-source compiler; if
  not, write to the Free Software Foundation, Inc., 675 Mass Ave,
  Cambridge, MA 02139, USA.
--------------------------------------------------------------------*/



#include "cxx-multifile.h"
#include "cxx-utils.h"
#include "cxx-driver-utils.h"
#include "filename.h"

#include <sys/types.h>
#include <dirent.h>

#include <string.h>
#include <sys/stat.h>

#include <ctype.h>
#include <errno.h>

#include <unistd.h>

#ifdef WIN32_BUILD
  #include <windows.h>
  #include <shellapi.h>
#endif

// int stat(const char *restrict path, struct stat *restrict buf);

char multifile_dir_exists(void)
{
    struct stat buf;
    memset(&buf, 0, sizeof(buf));

    if (stat(MULTIFILE_DIRECTORY, &buf) != 0)
    {
        return 0;
    }
    else
    {
        return S_ISDIR(buf.st_mode);
    }
}

void multifile_init_dir(void)
{
    if (multifile_dir_exists())
    {
        multifile_remove_dir();
    }

    mkdir(MULTIFILE_DIRECTORY, 0700);

    // Remove it, even if we are passed -k (-K would keep it)
    mark_dir_as_temporary(MULTIFILE_DIRECTORY);
}

void multifile_remove_dir(void)
{
    int result = 0;
#ifndef WIN32_BUILD
    // This is a bit lame but it is far easier than using nftw
    char c[256];
    snprintf(c, 255, "rm -r %s", MULTIFILE_DIRECTORY);
    result = (system(c) != 0);
#else
    SHFILEOPSTRUCT op_struct;
    memset(&op_struct, 0, sizeof(op_struct));
    op_struct.wFunc = FO_DELETE;
    char from[strlen(MULTIFILE_DIRECTORY) + 2];
    memset(from, 0, sizeof(from));
    strcpy(from, MULTIFILE_DIRECTORY);
    op_struct.pFrom = from;
    op_struct.fFlags = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_NOCONFIRMMKDIR;
    result = SHFileOperation(&op_struct);
#endif
    if (result != 0)
    {
        running_error("There was a problem when removing multifile temporal directory", 0);
    }
}

static void multifile_extract_extended_info_single_object(const char* filename)
{
    char only_section[256] = { 0 };
    snprintf(only_section, 255, "--only-section=%s", MULTIFILE_SECTION);
    only_section[255] = '\0';

    char output_filename[1024] = { 0 };
    snprintf(output_filename, 1023, "%s%s%s", MULTIFILE_DIRECTORY, DIR_SEPARATOR, MULTIFILE_TAR_FILE);
    output_filename[1023] = '\0';

    const char* arguments_objcopy[] = {
        "-Obinary",
        only_section,
        filename,
        output_filename,
        NULL
    };

    if (execute_program("objcopy", arguments_objcopy) != 0)
    {
        running_error("Error when extracting the object file data", 0);
    }

    // Now extract the tar

    const char* arguments_tar[] = {
        "xf",
        output_filename,
        "-C",
        MULTIFILE_DIRECTORY,
        ".",
        NULL
    };

    if (execute_program("tar", arguments_tar) != 0)
    {
        running_error("Error when extracting the object file tar", 0);
    }

    // Now remove the file
    if (remove(output_filename) < 0)
    {
        running_error("Error when removing temporal file '%s'. %s\n", 
                output_filename,
                strerror(errno));
    }
}

void multifile_extract_extended_info(const char* filename)
{
    // Maybe we should detect the file instead of relying on the extension?
    const char* extension = get_extension_filename(filename);
    if (extension != NULL
            && strcmp(extension, ".a") == 0)
    {
        // Note we rely on the POSIX 2008 behaviour, maybe we need a check in
        // configure?
        char *full_path = realpath(filename, NULL);

        char current_directory[1024] = { 0 };
        getcwd(current_directory, 1023);
        current_directory[1023] = '\0';

        // Change to temporal directory
        temporal_file_t temporal_dir = new_temporal_dir();
        chdir(temporal_dir->name);

        const char* list_arguments[] = {
            "x",
            full_path,
            NULL,
        };

        if (execute_program("ar", list_arguments) != 0)
        {
            running_error("Error while extracting members of archive", 0);
        }
        free(full_path);

        // Go back to previous directory
        chdir(current_directory);

        DIR* archive_dir = opendir(temporal_dir->name);
        // Now scan the temporary directory where we unpacked the archive
        struct dirent *dir_entry;

        dir_entry = readdir(archive_dir);
        while (dir_entry != NULL)
        {
            struct stat buf;
            memset(&buf, 0, sizeof(buf));

            char full_path[1024] = { 0 };

            snprintf(full_path, 1023, "%s%s%s", temporal_dir->name, DIR_SEPARATOR, dir_entry->d_name);
            full_path[1023] = '\0';

            // Recursively extract the info from this object (or maybe nested .a file, is this possible?)
            if (stat(full_path, &buf) == 0)
            {
                if (!S_ISDIR(buf.st_mode))
                {
                    if (multifile_object_has_extended_info(full_path))
                    {
                        multifile_extract_extended_info(full_path);
                    }
                }
            }
            dir_entry = readdir(archive_dir);
        }

        closedir(archive_dir);
    }
    else
    {
        multifile_extract_extended_info_single_object(filename);
    }
}

// This routine works both for .a and for .o thanks to objdump
char multifile_object_has_extended_info(const char* filename)
{
    temporal_file_t temp = new_temporal_file();

    const char* arguments[] =
    {
        "-w", 
        "-h",
        filename,
        NULL
    };

    // Should this 'objdump' be configurable?
    if (execute_program_flags("objdump", arguments, /* stdout_f */ temp->name, /* stderr_f */ NULL) != 0)
    {
        running_error("Error when identifying object file", 0);
    }

    FILE* stdout_file = fopen(temp->name, "r");

    if (stdout_file == NULL)
    {
        running_error("Error when examining output of 'objdump'", 0);
    }

    char line[256];

    char result = 0;

    while (fgets(line, 255, stdout_file) != NULL)
    {
        if ((strlen(line) > 1)
                && line[0] == ' ')
        {
            const char *q = line;

            // First blank part
            while (*q != '\0'
                    && (*q == ' ' || *q == '\t'))
                q++;

            if (*q == '\0')
                continue;

            // Index of the section
            while (*q != '\0'
                    && *q != ' '
                    && isdigit(*q))
                q++;

            if (*q == '\0' 
                    || *q != ' ')
                continue;

            // Second blank part
            while (*q != '\0'
                    && (*q == ' ' || *q == '\t'))
                q++;

            if (*q == '\0')
                continue;

            // Section name
            const char* p = q;

            while (*p != '\0'
                    && *p != ' ')
                p++;

            if (*p == '\0')
                continue;

            int num_chars = p - q;
            char name[num_chars + 1];
            strncpy(name, q, num_chars);
            name[num_chars] = '\0';

            if (strcmp(name, MULTIFILE_SECTION) == 0)
            {
                result = 1;
                break;
            }

        }
    }

    fclose(stdout_file);

    return result;
}


void multifile_get_extracted_profiles(const char*** multifile_profiles, int *num_multifile_profiles)
{
    // Profiles are stored in MULTIFILE_DIRECTORY/<directory>, each directory being a profile
    DIR* multifile_dir = opendir(MULTIFILE_DIRECTORY);
    if (multifile_dir == NULL)
    {
        if (errno != ENOENT)
        {
            // Only give an error if it does exist
            running_error("Cannot open multifile directory '%s'", MULTIFILE_DIRECTORY);
        }
    }
    else
    {
        struct dirent *dir_entry;

        dir_entry = readdir(multifile_dir);
        while (dir_entry != NULL)
        {
            struct stat buf;
            memset(&buf, 0, sizeof(buf));

            char full_path[1024] = { 0 };

            snprintf(full_path, 1023, "%s%s%s", MULTIFILE_DIRECTORY, DIR_SEPARATOR, dir_entry->d_name);
            full_path[1023] = '\0';

            if (stat(full_path, &buf) == 0)
            {
                if (S_ISDIR(buf.st_mode)
                        && dir_entry->d_name[0] != '.')
                {
                    const char* profile_name = uniquestr(dir_entry->d_name);
                    P_LIST_ADD(*multifile_profiles, *num_multifile_profiles, profile_name);
                }
            }

            dir_entry = readdir(multifile_dir);
        }

        closedir(multifile_dir);
    }
}

void multifile_get_profile_file_list(const char* profile_name,
        const char*** multifile_file_list,
        int *num_multifile_files)
{
    char profile_dir[1024];

    snprintf(profile_dir, 1023, "%s%s%s", MULTIFILE_DIRECTORY, DIR_SEPARATOR, profile_name);
    profile_dir[1023] = '\0';

    DIR* multifile_dir = opendir(profile_dir);
    if (multifile_dir == NULL)
    {
        if (errno != ENOENT)
        {
            // Only give an error if it does exist
            running_error("Cannot open multifile profile directory '%s'", profile_dir);
        }
    }
    else
    {
        struct dirent *dir_entry;

        dir_entry = readdir(multifile_dir);
        while (dir_entry != NULL)
        {
            struct stat buf;
            memset(&buf, 0, sizeof(buf));

            char full_path[1024] = { 0 };

            snprintf(full_path, 1023, "%s%s%s", profile_dir, DIR_SEPARATOR, dir_entry->d_name);
            full_path[1023] = '\0';

            if (stat(full_path, &buf) == 0)
            {
                if (dir_entry->d_name[0] != '.')
                {
                    const char* profile_name = strappend(profile_dir, 
                            strappend(DIR_SEPARATOR, dir_entry->d_name));
                    P_LIST_ADD(*multifile_file_list, *num_multifile_files, profile_name);
                }
            }

            dir_entry = readdir(multifile_dir);
        }

        closedir(multifile_dir);
    }
}

typedef
struct embed_bfd_data_tag
{
    temporal_file_t temp_dir;
} embed_bfd_data_t;

void multifile_embed_bfd_single(void** data, compilation_file_process_t* secondary_compilation_file)
{
    embed_bfd_data_t* embed_data = NULL;
    if (*data == NULL)
    {
        (*data) = calloc(1, sizeof(embed_bfd_data_t));
         embed_data = (embed_bfd_data_t*)(*data);
        
        // Create the temporal directory
        embed_data->temp_dir = new_temporal_dir();
    }
    else
    {
        embed_data = (embed_bfd_data_t*)(*data);
    }


    translation_unit_t* current_secondary = secondary_compilation_file->translation_unit;
    compilation_configuration_t* secondary_configuration = secondary_compilation_file->compilation_configuration;

    char dir_path[1024];
    snprintf(dir_path, 1023, "%s%s%s", 
            embed_data->temp_dir->name, 
            DIR_SEPARATOR, 
            secondary_configuration->configuration_name);
    dir_path[1023] = '\0';

    struct stat buf;
    int res = stat(dir_path, &buf);

    if (res != 0)
    {
        if (errno == ENOENT)
        {
            // Create the directory if it does not exist
            if (mkdir(dir_path, 0700) != 0)
            {
                running_error("When creating multifile archive, cannot create directory '%s': %s\n",
                        dir_path,
                        strerror(errno));
            }
        }
        else
        {
            running_error("Stat failed on '%s': %s\n",
                    dir_path,
                    strerror(errno));
        }
    }
    else
    {
        if (!S_ISDIR(buf.st_mode))
        {
            running_error("When creating multifile archive, path '%s' is not a directory\n",
                    dir_path);
        }
    }

    // Now move the secondary file

    char dest_path[1024];
    snprintf(dest_path, 1023, "%s%s%s", 
            dir_path, 
            DIR_SEPARATOR, 
            give_basename(current_secondary->output_filename));

    if (move_file(current_secondary->output_filename, dest_path) != 0)
    {
        running_error("When creating multifile archive, file '%s' could not be moved to '%s'\n",
                current_secondary->output_filename,
                dest_path);
    }
}

void multifile_embed_bfd_collective(void **data, const char* output_filename)
{
    ERROR_CONDITION((*data == NULL), "This cannot be NULL", 0);
    embed_bfd_data_t* embed_data  = (embed_bfd_data_t*)(*data);

    // Now all files have been moved into the temporal directory, run the tar there
    temporal_file_t new_tar_file = new_temporal_file_extension(".tar");
    const char* tar_args[] =
    {
        "cf",
        new_tar_file->name,
        "-C", embed_data->temp_dir->name,
        ".",
        NULL
    };

    if (execute_program("tar", tar_args) != 0)
    {
        running_error("When creating multifile archive, 'tar' failed\n");
    }

    // Now we have tar that we are going to embed into the .o file

    // objcopy --add-section .mercurium=architectures.tar --set-section-flags .mercurium=alloc,readonly prova.o

    char multifile_section_and_file[1024], multifile_section_and_flags[1024];

    snprintf(multifile_section_and_file, 1023, "%s=%s",
            MULTIFILE_SECTION, new_tar_file->name);
    multifile_section_and_file[1023] = '\0';

    snprintf(multifile_section_and_flags, 1023, "%s=alloc,readonly",
            MULTIFILE_SECTION);
    multifile_section_and_flags[1023] = '\0';

    const char* objcopy_args[] =
    {
        "--add-section", multifile_section_and_file, 
        "--set-section-flags", multifile_section_and_flags,
        output_filename,
        NULL,
    };

    if (execute_program("objcopy", objcopy_args) != 0)
    {
        running_error("When creating multifile archive, 'objcopy' failed\n");
    }

    if (CURRENT_CONFIGURATION->verbose)
    {
        fprintf(stderr, "Secondary files successfully embedded into '%s' file\n", 
                output_filename);
    }
}
