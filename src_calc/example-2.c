#include <gtk/gtk.h>
#include <locale.h>

#include "s21_calc.h"
#include "s21_parsing.h"

static void print_hello(GtkWidget *widget, gpointer data) {
    g_print("%s", data);
}
static void delete_text(GtkWidget *widget, gpointer data) {
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(data));
    unsigned len = gtk_entry_buffer_get_length(buffer);
    gtk_entry_buffer_delete_text(buffer, len - 1, 1);
}
static void add_func(GtkWidget *widget, gpointer data) {
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(data));
    const char *str = gtk_button_get_label(GTK_BUTTON(widget));
    gtk_entry_buffer_insert_text(buffer, gtk_entry_buffer_get_length(buffer),
                                 str, -1);
}
static void add_bracket(GtkWidget *widget, gpointer data) {
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(data));
    gtk_entry_buffer_insert_text(buffer, gtk_entry_buffer_get_length(buffer),
                                 "(", -1);
}
static void delete_all_text(GtkWidget *widget, gpointer data) {
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(data));
    if (gtk_entry_buffer_get_length(buffer) > 0) {
        gtk_entry_buffer_emit_deleted_text(buffer, 0,
                                           gtk_entry_buffer_get_length(buffer));
    }
}
static void add_pi(GtkWidget *widget, gpointer data) {
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(data));
    gtk_entry_buffer_insert_text(buffer, gtk_entry_buffer_get_length(buffer),
                                 "3.14159265359", -1);
}
static void add_exp(GtkWidget *widget, gpointer data) {
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(data));
    gtk_entry_buffer_insert_text(buffer, gtk_entry_buffer_get_length(buffer),
                                 "2.7182818284", -1);
}
static void ok_lets_go(GtkWidget *widget, gpointer data) {
    setlocale(LC_ALL, "en_US.utf8");
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(data));
    g_print("data = [%s]\n", data);
    const char *calk = gtk_entry_buffer_get_text(buffer);
    g_print("calk = [%s]\n", calk);
    double result = parsing((char *)calk);
    g_print("result = [%lf]\n", result);
    char *res = (char *)calloc(MAX_LINE, sizeof(char));
    snprintf(res, MAX_LINE, "%.7lf", result);
    gtk_entry_buffer_set_text(buffer, res, strlen(res));
    free(res);
    free((char *)calk);
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *okno;
    GtkEntryBuffer *v_okne;

    //создаем новое окно и устанавливаем его заголовок
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Mabobbi calculator");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_widget_set_can_focus(window, FALSE);
    // gtk_widget_get_can_focus(window);

    //Здесь мы создаем контейнер, который будет упаковывать наши кнопки
    grid = gtk_grid_new();

    //Запаковываем контейнер в окно
    gtk_window_set_child(GTK_WINDOW(window), grid);

    //Поместите первую кнопку в ячейку сетки(0, 0) и заставьте ее заполнить
    //*только 1 ячейку по горизонтали и вертикали(т.е.без перекрытия)
    v_okne = gtk_entry_buffer_new("", -1);
    okno = gtk_entry_new_with_buffer(v_okne);
    gtk_grid_attach(GTK_GRID(grid), okno, 0, 0, 8, 1);

    button = gtk_button_new_with_label("delete");
    g_signal_connect(button, "clicked", G_CALLBACK(delete_all_text), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 1, 1);
    button = gtk_button_new_with_label("graph");
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
    gtk_grid_attach(GTK_GRID(grid), button, 1, 1, 1, 1);
    button = gtk_button_new_with_label("asin");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    g_signal_connect(button, "clicked", G_CALLBACK(add_bracket), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 2, 1, 1);
    button = gtk_button_new_with_label("acos");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    g_signal_connect(button, "clicked", G_CALLBACK(add_bracket), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 3, 1, 1);
    button = gtk_button_new_with_label("atan");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    g_signal_connect(button, "clicked", G_CALLBACK(add_bracket), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 4, 1, 1);
    button = gtk_button_new_with_label("pi");
    g_signal_connect(button, "clicked", G_CALLBACK(add_pi), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 5, 1, 1);

    button = gtk_button_new_with_label("sin");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    g_signal_connect(button, "clicked", G_CALLBACK(add_bracket), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 1, 2, 1, 1);
    button = gtk_button_new_with_label("cos");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    g_signal_connect(button, "clicked", G_CALLBACK(add_bracket), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 1, 3, 1, 1);
    button = gtk_button_new_with_label("tan");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    g_signal_connect(button, "clicked", G_CALLBACK(add_bracket), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 1, 4, 1, 1);
    button = gtk_button_new_with_label("EXP");
    g_signal_connect(button, "clicked", G_CALLBACK(add_exp), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 1, 5, 1, 1);

    button = gtk_button_new_with_label("x");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 2, 1, 1, 1);
    button = gtk_button_new_with_label("ln");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    g_signal_connect(button, "clicked", G_CALLBACK(add_bracket), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 2, 2, 1, 1);
    button = gtk_button_new_with_label("log");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    g_signal_connect(button, "clicked", G_CALLBACK(add_bracket), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 2, 3, 1, 1);
    button = gtk_button_new_with_label("sqrt");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    g_signal_connect(button, "clicked", G_CALLBACK(add_bracket), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 2, 4, 1, 1);
    button = gtk_button_new_with_label("^");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 2, 5, 1, 1);

    button = gtk_button_new_with_label("(");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 3, 1, 1, 1);
    button = gtk_button_new_with_label("7");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 3, 2, 1, 1);
    button = gtk_button_new_with_label("4");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 3, 3, 1, 1);
    button = gtk_button_new_with_label("1");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 3, 4, 1, 1);
    button = gtk_button_new_with_label("0");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 3, 5, 1, 1);

    button = gtk_button_new_with_label(")");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 5, 1, 1, 1);
    button = gtk_button_new_with_label("8");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 5, 2, 1, 1);
    button = gtk_button_new_with_label("5");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 5, 3, 1, 1);
    button = gtk_button_new_with_label("2");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 5, 4, 1, 1);
    button = gtk_button_new_with_label(".");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 5, 5, 1, 1);

    button = gtk_button_new_with_label("%");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 6, 1, 1, 1);
    button = gtk_button_new_with_label("9");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 6, 2, 1, 1);
    button = gtk_button_new_with_label("6");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 6, 3, 1, 1);
    button = gtk_button_new_with_label("3");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 6, 4, 1, 1);
    button = gtk_button_new_with_label("=");
    g_signal_connect(button, "clicked", G_CALLBACK(ok_lets_go), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 6, 5, 1, 1);

    button = gtk_button_new_with_label("AC");
    g_signal_connect(button, "clicked", G_CALLBACK(delete_text), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 7, 1, 1, 1);
    button = gtk_button_new_with_label("/");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 7, 2, 1, 1);
    button = gtk_button_new_with_label("*");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 7, 3, 1, 1);
    button = gtk_button_new_with_label("-");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 7, 4, 1, 1);
    button = gtk_button_new_with_label("+");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 7, 5, 1, 1);

    gtk_widget_show(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}