build: quick_sort.cpp merge_sort.cpp
	g++ quick_sort.cpp -o quicksort
	g++ merge_sort.cpp -o mergesort

run: quicksort mergesort
	./quicksort < input.txt > quicksort_opt.txt
	./mergesort < input.txt > mergesort_opt.txt


clean: mergesort quicksort mergesort_opt.txt
	rm mergesort
	rm quicksort
	rm mergesort_opt.txt
	rm quicksort_opt.txt