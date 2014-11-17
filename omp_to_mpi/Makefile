# IMPORTANT: Do not forget to fill the two variables in Makefile.common

all:	
	@echo ""
	@echo "BEGIN build custom phases..."
	@make -C ./trans/
	@echo "---------------------------------------------------------------------------"
	@echo "END build custom phases."
	@echo ""


install:
	@echo ""
	@echo "Installing custom phases..."
	@make -C ./trans/ install

	@echo ""

clean:
	@make -C ./trans/ clean
