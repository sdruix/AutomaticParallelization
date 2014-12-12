# IMPORTANT: Do not forget to fill the two variables in Makefile.common

all:	
	@echo ""
	@echo "BEGIN build custom phases..."
	@make -C ./forNormalization/
	@echo "---------------------------------------------------------------------------"
	@echo "END build custom phases."
	@echo ""


install:
	@echo ""
	@echo "Installing custom phases..."
	@make -C ./forNormalization/ install
	@echo ""

clean:
	@make -C ./forNormalization/ clean