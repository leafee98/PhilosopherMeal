help:
	@echo "    Usage: make {target}"
	@echo ""
	@echo "    you can just type 'make {target}' and get an executable file"
	@echo "    named 'a.out', you can run it to see its performance."
	@echo ""
	@echo "    the available target is follow:"
	@echo "        most4        most 4 philosophers eat at same time"
	@echo "        odd_even     odd get left and even get right"
	@echo "        dielock      there is nothing done to prevent dielock"
	@echo ""

most4:
	@echo "  now using 'most4' as target"
	g++ src/main_most4.cpp src/mysemop.cpp src/philosopher.cpp -o a.out

odd_even:
	@echo "  now using 'odd_even' as target"
	g++ src/main_odd_even.cpp src/mysemop.cpp src/philosopher.cpp -o a.out

dielock:
	@echo "  now using 'dielock' as target"
	g++ src/main_dielock.cpp src/mysemop.cpp src/philosopher.cpp -o a.out

