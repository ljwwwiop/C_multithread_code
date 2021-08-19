cc = g++
prom = demo
obj = main.o Aclass/product.o Bclass/employee.o
deps = product.h employee.h

$(prom) : $(obj)
	$(cc) -o $(prom) $(obj)

%.o : %.c $(deps)
	$(cc) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(obj) $(prom)


 
