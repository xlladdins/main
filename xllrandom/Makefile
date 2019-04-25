MKDN = $(wildcard *.md)
HTML = $(MKDN:.md=.html)
FLAGS = -s --katex

$(HTML): %.html: %.md
	pandoc $(FLAGS) $< -o $@
	sed -i '1s/^/LR"xyzzyx(\n/' $@
	echo ")xyzzyx\"\n" >> $@
