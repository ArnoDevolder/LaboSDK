#include <gtk/gtk.h>
#include "PJ_RPI.h"
#include <stdio.h>

/* Functions START */

int stateLED2 = 0;
int stateLED1 = 0;
int stateSW1 = 0;
int stateSW2 = 0;
char buffer[30];

void click_function(GtkWidget *wid, gpointer ptr)
{
        // Var
        char buff[30];
        // OFF
        if (GPIO_READ(17))
        {
        GPIO_CLR = 1 << 17;
        stateLED1 = 0;
        sprintf(buff, "led1 is : %d",stateLED1);
        gtk_label_set_text(GTK_LABEL (ptr), buff);
        printf("gpio: %d off \n",17);
        }
        // ON
        else
        {
        GPIO_SET = 1 << 17;
        stateLED1 = 1;
        sprintf(buff, "led1 is : %d",stateLED1);
        gtk_label_set_text(GTK_LABEL (ptr), buff);
        printf("gpio: %d on \n",17);
        }  
}

void click_function2(GtkWidget *wid, gpointer ptr)
{
        char buff[30];
        // OFF
        if (GPIO_READ(22))
        {
        GPIO_CLR = 1 << 22;
        stateLED2 = 0;
        sprintf(buff, "led2 is : %d",stateLED2);
        gtk_label_set_text(GTK_LABEL (ptr), buff);
        printf("gpio: %d off \n",22);
        }
        // OFF
        else
        {
        GPIO_SET = 1 << 22;
        stateLED2 = 1;
        sprintf(buff, "led2 is : %d",stateLED2);
        gtk_label_set_text(GTK_LABEL (ptr), buff);
        printf("gpio: %d on \n",22);
        }    
}

void click_function3(GtkWidget *wid, gpointer ptr)
{
    char buff[30];
    // IF INPUT GPIO IS 1
    if(GPIO_READ(23)) 
    {
        stateSW1=1;
        sprintf(buff, "SW1 is : %d",stateSW1);
        gtk_label_set_text(GTK_LABEL (ptr), buff);
        printf("gpio: %d true \n",23);
    }
    // IF INPUT GPIO IS 0
    else 
    {
        stateSW1=0;
        sprintf(buff, "SW1 is : %d",stateSW1);
        gtk_label_set_text(GTK_LABEL (ptr), buff);
        printf("gpio: %d false \n",23);
    }
}

void click_function4(GtkWidget *wid, gpointer ptr)
{
    char buff[30];
    // IF INPUT GPIO IS 1
    if(GPIO_READ(24)) 
    {
        stateSW2=1;
        sprintf(buff, "SW2 is : %d",stateSW2);
        gtk_label_set_text(GTK_LABEL (ptr), buff);
        printf("gpio: %d true \n",24);
    }
    // IF INPUT GPIO IS 0
    else 
    {
        stateSW2=0;
        sprintf(buff, "SW2 is : %d",stateSW2);
        gtk_label_set_text(GTK_LABEL (ptr), buff);
        printf("gpio: %d false \n",24);
    }
}
/* Functions STOP */



/* main START */

int main (int argc, char *argv[])
{
       // Libary Check
        if(map_peripheral(&gpio) == -1) 
	{
		printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
		return -1;
	}

    // Define GPIOS
    //LED1
    INP_GPIO(17);
    OUT_GPIO(17);
    //LED2
    INP_GPIO(22);
    OUT_GPIO(22);
    //SW1
    OUT_GPIO(23);
    INP_GPIO(23);
    //SW2
    OUT_GPIO(24);
    INP_GPIO(24);

    if (GPIO_READ(17)){stateLED1 = 1;}else{stateLED1 = 0;}
    if (GPIO_READ(22)){stateLED2 = 1;}else{stateLED2 = 0;}
    if (GPIO_READ(23)){stateSW1 = 1;}else{stateSW1 = 0;}
    if (GPIO_READ(24)){stateSW2 = 1;}else{stateSW2 = 0;}   

    gtk_init (&argc, &argv);
    GtkWidget *win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_show (win);
    // Make Buttons
    GtkWidget *btn = gtk_button_new_with_label("LED1");
    GtkWidget *btn2 = gtk_button_new_with_label("LED2");
    GtkWidget *btn3 = gtk_button_new_with_label("CHECK INPUT SW1");
    GtkWidget *btn4 = gtk_button_new_with_label("CHECK INPUT SW2");
    // Make Labels + buf states
    sprintf(buffer, "led1 is : %d",stateLED1);
    GtkWidget *lbl = gtk_label_new(buffer);
    sprintf(buffer, "led2 is : %d",stateLED2);
    GtkWidget *lbl2 = gtk_label_new(buffer);
    sprintf(buffer, "SW2 is : %d",stateSW1);
    GtkWidget *lbl3 = gtk_label_new(buffer);
    sprintf(buffer, "SW2 is : %d",stateSW2);
    GtkWidget *lbl4 = gtk_label_new(buffer);
    // Make Box (er kan maar 1 iets geadd worden dus maken we een grote box van alle elementen)
    GtkWidget *box = gtk_vbox_new (FALSE, 5);
    gtk_box_pack_start (GTK_BOX (box), btn, TRUE,TRUE,0); //LED1 - OUT
    gtk_box_pack_start (GTK_BOX (box), lbl, TRUE,TRUE,0);
    gtk_box_pack_start (GTK_BOX (box), btn2, TRUE,TRUE,0); //LED2 - OUT
    gtk_box_pack_start (GTK_BOX (box), lbl2, TRUE,TRUE,0);
    gtk_box_pack_start (GTK_BOX (box), btn3, TRUE,TRUE,0); //SW1 - INP
    gtk_box_pack_start (GTK_BOX (box), lbl3, TRUE,TRUE,0);
    gtk_box_pack_start (GTK_BOX (box), btn4, TRUE,TRUE,0); //SW2 - INP
    gtk_box_pack_start (GTK_BOX (box), lbl4, TRUE,TRUE,0);
    // Function Toevoegen
    g_signal_connect(btn, "clicked", G_CALLBACK(click_function),
        lbl);
    g_signal_connect(btn2, "clicked", G_CALLBACK(click_function2),
        lbl2);
    g_signal_connect(btn3, "clicked", G_CALLBACK(click_function3),
        lbl3);
    g_signal_connect(btn4, "clicked", G_CALLBACK(click_function4),
        lbl4);    
    // box Toevoegen aan container/window
    gtk_container_add(GTK_CONTAINER(win), box);
    gtk_widget_show_all(win);
    gtk_main ();
    return 0;
}

/* main STOP */