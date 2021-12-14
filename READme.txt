/* COMMANDS GTK EMBED */

/ * libarys */

pkg-config --cflags --libs gtk+-2.0

/* compileren */

gcc `pkg-config --cflags --libs gtk+-2.0` gtktest.c -o gtktest

/* compileren met PJ libary */

gcc `pkg-config --cflags --libs gtk+-2.0` gtktest.c -l PJ_RPI  -o gtktest

/* GPIOS UITLEZEN */

gpio readall 