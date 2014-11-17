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


#ifndef NANOX_DEVICES_H
#define NANOX_DEVICES_H

#include "tl-compilerphase.hpp"
#include "tl-objectlist.hpp"
#include "tl-data-env.hpp"

namespace TL {

namespace Nanox
{
    /*!
      This class holds additional info which is used by the DeviceProvider to create
      the outline
      */
    struct OutlineFlags
    {
        /*! 
          If this flag is true, the outline should perform a barrier at the end
          using the proper device dependent interface.
          */
        bool barrier_at_end;

        /*! 
          If this flag is true, the generated outline has to be created for the implicit tasks of a
          parallel region.
          */
        bool parallel;

        /*!
          If this flag is true, the device provider should not try to create a name
          after the outline one. Just use it as is. This is needed for targets
          whose code is already implemented
          */
        bool implemented_outline;

        /*!
          This symbol represents the task function called from the outline.
          */
        Symbol task_symbol;

        OutlineFlags()
            : barrier_at_end(false),
            parallel(false),
            implemented_outline(false),
            task_symbol(NULL)
        {
        }
    };

    /*!
      This class should be implemented by each device supported in Nanos++
      */
    class DeviceProvider : public TL::CompilerPhase
    {
        protected:
            bool instrumentation_enabled();

            bool do_not_create_translation_function();

            bool create_translation_function();

            const std::string _device_name;
        private:
            bool _enable_instrumentation;
            std::string _enable_instrumentation_str;
            void set_instrumentation(const std::string& str)
            {
                _enable_instrumentation = false;
                parse_boolean_option(/* Parameter name */ "instrument", 
                        /* Given value */ str, 
                        /* Computed bool */ _enable_instrumentation, 
                        /* Error message */  "Instrumentation disabled");
            }

            bool _do_not_create_translation_fun;
            std::string _do_not_create_translation_str;
            void set_translation_function_flag(const std::string& str)
            {
                _do_not_create_translation_fun = false;
                parse_boolean_option("do_not_create_translation_function", 
                        str, _do_not_create_translation_fun, "Assuming false.");
            }

            void common_constructor_code();

        public:
            //! Constructor of a DeviceProvider
            /*!
              \param device_name Device's identifier name
              DeviceProvider::needs_copies can be used to retrieve this value
             */
            DeviceProvider(const std::string& device_name);

            //! States if this device needs copies
            /*!
              Obsolete function. It always returns true
              */
            DEPRECATED bool needs_copies() const
            {
                return true;
            }

            std::string get_name() const
            {
                return _device_name;
            }

            virtual void pre_run(DTO& dto){};
            virtual void run(DTO& dto) { }

            /*!
              This function creates the outline which will run the parallel code

              \param task_name This is the name of the task. It is a valid C/C++ identifier unique to the current spawned task
              \param struct_typename This is the type name of the argument structure. This is the type created at the spawn
                                     side to hold the arguments. For some devices this name is of no use or can be used just
                                     to create another name
              \param data_environ This is the data environment of this task. See the documentation of DataEnvironInfo for more details
              \param outline_flags These are outline flags which drive some details of the created outline
              \param reference_tree This is a reference tree from the spawn point which led to the creation of this outline
              \param sl ScopeLink
              \param initial_setup This is a device-dependent code which can contain initial setup code required by the outline. This code
                                   is derived from the replace_setup parameter of do_replacements. This code must be embedded in the outline
                                   before outline_body
              \param outline_body The body of the outline. This body is normally derived from replaced_src parameter of do_replacements
              */
            virtual void create_outline(
                    const std::string& task_name,
                    const std::string& struct_typename,
                    DataEnvironInfo &data_environ,
                    const OutlineFlags& outline_flags,
                    AST_t reference_tree,
                    ScopeLink sl,
                    Source initial_setup,
                    Source outline_body) = 0;

            /*!
              This function performs the replacements required to implement the outline according to the
              current data_environ. It returns two Source, once containing the (optional) initial setup for
              replacements, and another one for the replaced body itself

              \param data_environ Data environment of the task. See the documentation of DataEnvironInfo for more details
              \param body The tree to have its variables replaced according to \a data_environ
              \param scope_link ScopeLink
              \param replace_setup Output parameter of code that may be required to properly perform the replacements. Sometimes some
                                   adjustments (like castings) are required for proper replacements
              \param replaced_src Output parameter of the code of \a body once replaced using \a data_environ
             */
            virtual void do_replacements(DataEnvironInfo& data_environ,
                    AST_t body,
                    ScopeLink scope_link,
                    Source &replace_setup,
                    Source &replaced_src) = 0;

            /*! 
              This function returns the device descriptor for nanos_devices_t

              \param task_name This is the name of the task. It is a valid C/C++ identifier unique to the current task
              \param data_environ Data environment of the task. See the documentation of DataEnvironInfo for more details
              \param outline_flags These are outline flags which drive some details of the created outline
              \param ancillary_device_description Some devices may require additional code to properly initialize the device descriptor
              \param device_descriptor The device descriptor itself as an initializer of nanos_devices_t
              */
            virtual void get_device_descriptor(const std::string& task_name,
                    DataEnvironInfo &data_environ,
                    const OutlineFlags& outline_flags,
                    AST_t reference_tree,
                    ScopeLink sl,
                    Source &ancillary_device_description,
                    Source &device_descriptor) = 0;

            /*!
              This function adds a new function definition to a device. Its
              default implementation simply removes the pragma.

              When a #pragma omp target is used on a function definition the
              compiler will call this function.
              
              \param owned_tree States whether \a ctr is a copy of the original
              or not. When it is not a copy, the DeviceProvider can remove the
              whole pragma if needed
              */
            virtual void insert_function_definition(PragmaCustomConstruct ctr, bool is_copy) 
            { 
                internal_error("Device '%s' does not provide a way to insert a function definition\n", 
                        _device_name.c_str());
            }

            /*!
              This function adds a new declaration to a device. 
              Its default implementation simply removes the pragma.

              When a #pragma omp target is used on a declaration (other than a
              function definition) the compiler will call this function.

              \param owned_tree States whether \a ctr is a copy of the original
              or not. When it is not a copy, the DeviceProvider can remove the
              whole pragma if needed
              */
            virtual void insert_declaration(PragmaCustomConstruct ctr, bool is_copy) 
            { 
                internal_error("Device '%s' does not provide a way to insert a declaration\n", 
                        _device_name.c_str());
            }

            /*!
              This function returns the source code for gathering an omp reduction
              
              \param reduction_references List of reduction references in the current environment
             */
            virtual Source get_reduction_code(
                    ObjectList<OpenMP::ReductionSymbol> reduction_references, 
                    ScopeLink)
            {
                return Source();
            }
                    
            virtual ~DeviceProvider() { }
    };

    class DeviceHandler
    {
        public:
            static DeviceHandler& get_device_handler();

            void register_device(DeviceProvider* nanox_device_provider);
            
            void register_device(const std::string& str, 
                    DeviceProvider* nanox_device_provider);

            DeviceProvider* get_device(const std::string& str);

        private:
            typedef std::map<std::string, DeviceProvider*> nanox_devices_map_t;
            nanox_devices_map_t _nanox_devices;
    };
}

}

#endif // NANOX_DEVICES_H
