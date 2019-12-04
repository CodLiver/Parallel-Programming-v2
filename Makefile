compile: jacobi2dSerial.c jacobi2d.c
	@gcc -fopenmp -O3 jacobi2dSerial.c -o jacobiSerial1
	@gcc -fopenmp -O3 jacobi2d.c -o jacobiSerial0
	@echo "compiled"
	
serComp: 
	@gcc -fopenmp jacobi2dSerial.c -o jacobiSerial1

parComp: 
	@gcc -fopenmp jacobi2d.c -o jacobiSerial0
	
parShort:
	@./jacobiSerial0 5 5 0.0000000001

parLong:
	@./jacobiSerial0 120 120 0.0000000001
	

serShort:
	@./jacobiSerial1 5 5 0.0000000001

serLong:
	@./jacobiSerial1 120 120 0.0000000001
	
	
allShort:
	@echo "---------Parallel---------"
	@./jacobiSerial0 5 5 0.0000000001
	@echo "---------Serial---------"
	@./jacobiSerial1 5 5 0.0000000001

allLong:
	@echo "---------Parallel---------"
	@./jacobiSerial0 120 120 0.0000000001
	@echo "---------Serial---------"
	@./jacobiSerial1 120 120 0.0000000001
	
allCustom: 
	@echo "---------Parallel---------"
	@./jacobiSerial0 $(M) $(N) $(STDDEV)
	@echo "---------Serial---------"
	@./jacobiSerial1 $(M) $(N) $(STDDEV)
	

parCustom:
	@./jacobiSerial0 $(M) $(N) $(STDDEV)	
	
serCustom:
	@./jacobiSerial1 $(M) $(N) $(STDDEV)


help:
	@echo "compSer&Par"
	@echo "parShort&Long 5,120"
	@echo "serShort&Long 5,120"
	@echo "allShort&Long 5,120"
	@echo "all&ser&parCust: make M='5' N='5' STDDEV='0.0000000001' all&ser&parcustom"
	
	

	