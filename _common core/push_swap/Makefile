# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanghi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 17:55:23 by aanghi            #+#    #+#              #
#    Updated: 2024/01/18 17:55:23 by aanghi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += -s

NAME =   push_swap
CFLAGS = -Wall -Wextra -Werror

MAINP = main.c
OBJP = $(MAINP:.c=.o)

MAINC = checker.c
OBJC = $(MAINC:.c=.o)

SRC = utilitis.c marshal.c operations.c \
	  sort.c sort1.c \
	  get_next_line.c get_next_line_utils.c \
	  ft_split.c ft_substr.c ft_strlen.c ft_atoi.c ft_strncmp.c ft_putstr.c \
	  ft_lstadd_back.c ft_lstlen.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(OBJP)
	gcc -o $(NAME) $(OBJ) $(OBJP)

bonus: $(OBJ) $(OBJC)
	gcc -o checker $(OBJ) $(OBJC)

clean:
	rm -f $(OBJ)
	rm -f $(OBJC)
	rm -f $(OBJP)
	rm -f $(OBJC)

fclean: clean
	rm -f $(NAME)
	rm -f checker

re: fclean all

git: fclean
	@rm -f .DS_Store
	@git add .
	@git commit -m "commit"
	@git push

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

test: re bonus
	rm -f $(OBJ)
	rm -f $(OBJC)
	rm -f $(OBJP)
	rm -f $(OBJC)
	clear
	echo ./$(NAME)
	-./$(NAME)
	echo
	echo ./$(NAME) '""'
	-./$(NAME) ""
	echo
	echo ./$(NAME) "''"
	-./$(NAME) ''
	echo
	echo ./$(NAME) '"   "'
	-./$(NAME) "   "
	echo
	echo ./$(NAME) 42 42
	-./$(NAME) 42 42
	echo
	echo ./$(NAME) Voglio mangiare il tuo pancreas
	-./$(NAME) Voglio mangiare il tuo pancreas
	echo
	echo ./$(NAME) '"Voglio mangiare il tuo pancreas"'
	-./$(NAME) "Voglio mangiare il tuo pancreas"
	echo
	echo ./$(NAME) '"Voglio mangiare il tuo pancreas"' 42
	-./$(NAME) "Voglio mangiare il tuo pancreas" 42
	echo
	echo ./$(NAME) '"42"' Voglio mangiare il tuo pancreas
	-./$(NAME) "42" Voglio mangiare il tuo pancreas
	echo
	echo ./$(NAME) '"++42"'
	-./$(NAME) "++42"
	echo
	echo ./$(NAME) '"--42"'
	-./$(NAME) "--42"
	echo
	echo ./$(NAME) 43 '"42 7 18 12"' 23
	-./$(NAME) 43 "42 7 18 12" 23
	echo
	echo ./$(NAME) \"\'\'\"
	-./$(NAME) "''"
	read
	clear
	echo ./$(NAME) $(ARGS)
	./$(NAME) $(ARGS)
	@echo
	@echo "N. mosse: "
	@./$(NAME) $(ARGS) | wc -l
	@echo
	@echo "Corretto: "
	@./$(NAME) $(ARGS) | ./checker $(ARGS)
	@echo
	@echo Norminette error: 
	norminette | grep Error! | wc -l
	@echo
	@echo "Leaks: $(NAME)"
	@leaks -atExit -- ./$(NAME) $(ARGS) > temp.txt
	cat temp.txt | grep "total leaked bytes."
	echo 
	@echo "Leaks: checker"
	@leaks -atExit -- ./checker > temp.txt
	cat temp.txt | grep "total leaked bytes."
	rm temp.txt
	@rm -f $(NAME)
	@rm -f checker

#ARGS = 42 7
#ARGS = 42 7 18
ARGS = 265 646 244 977 704 172 967 434 995 175 252 740 817 697 393 788 804 613 764 689 129 388 417 308 768 352 807 881 230 878 49 70 912 627 823 95 195 949 847 825 112 214 3 886 520 737 836 822 257 290 305 466 595 548 950 809 361 373 919 572 535 319 761 610 668 240 897 494 965 6 895 941 422 551 410 982 834 991 696 773 79 879 664 968 165 169 887 571 661 934 980 782 406 371 321 497 821 304 961 384
#ARGS = 105 884 773 539 762 532 87 541 430 622 94 794 804 475 47 123 957 809 489 559 57 791 222 298 974 64 626 610 511 845 582 519 729 65 213 374 912 544 53 967 694 616 190 193 432 316 451 918 479 390 691 250 439 864 100 405 224 978 280 923 66 796 285 944 252 35 196 866 520 770 533 888 932 28 611 747 503 921 526 990 704 371 259 338 217 970 462 578 443 130 73 124 814 287 59 732 411 645 963 594 167 1 38 43 821 36 919 595 678 758 92 719 49 364 588 237 538 2 994 112 812 556 914 307 166 685 515 514 103 7 717 554 931 721 938 186 453 903 965 992 306 274 255 930 818 831 304 174 662 235 339 568 459 848 308 935 737 761 296 145 134 835 27 646 720 665 253 289 30 591 294 634 731 157 418 290 567 329 782 273 982 312 929 751 649 309 266 956 181 403 261 366 179 771 345 749 386 328 617 768 790 342 201 354 305 351 117 428 396 777 243 902 807 672 272 926 392 376 766 607 321 495 225 647 798 619 297 327 530 583 48 151 470 446 153 120 971 211 344 139 491 563 788 723 155 118 783 632 107 968 674 826 792 654 707 317 599 703 734 684 523 183 641 375 624 637 846 399 146 90 228 802 776 216 251 580 996 955 628 587 764 60 722 803 466 787 680 535 458 143 485 668 644 995 877 23 422 509 407 236 819 865 676 142 615 218 683 592 570 738 393 613 452 50 37 636 457 945 833 16 68 987 872 477 25 89 806 450 496 331 425 464 780 61 513 893 997 620 986 397 655 512 440 9 205 420 52 834 603 648 426 269 463 585 191 859 740 505 93 144 6 808 579 863 891 122 840 353 471 869 608 690 365 602 813 11 8 12 656 138 889 871 21 552 311 961 114 85 695 853 639 349 890 435 404 564 897 75 121 473 664 653 215 767 881 561 467 220 687 229 688 500 158 433 784 337 928 91 741 279 484 799 180 686 901 781 925 972 230 700 227 330 870 341 178 713 827 79 110 184 104 488 135 847 666 958 424 769 24 410 32 725 395 801 292 618 755 702 379 56 904 455 80 800 483 856 249 276 553 815 360 343 71 315 176 454 936 699 524 136 661 465 408 759 197 169 934 111 874 939 499 510 333 198 574 244 10 868 177 915
#ARGS = "   42 7 18 12   "
#ARGS = "42 7 18 12"
