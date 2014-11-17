# IMPORTANT: Do not forget to fill the two variables in Makefile.common

all:	
	@echo ""
	@echo "BEGIN build custom phases..."
	@make -C ./inline/
	@echo "---------------------------------------------------------------------------"
	@make -C ./outline/
	@echo "---------------------------------------------------------------------------"
	@make -C ./s2s/
	@echo "---------------------------------------------------------------------------"
	@echo "END build custom phases."
	@echo ""


install:
	@echo ""
	@echo "Installing custom phases..."
	@make -C ./inline/ install
	@make -C ./outline/ install
	@make -C ./s2s/ install
	@echo ""

clean:
	@make -C ./inline/ clean
	@make -C ./outline/ clean
	@make -C ./s2s/ clean
