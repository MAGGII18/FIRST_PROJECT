#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>

// --- Simulated backend plagiarism function ---
double check_plagiarism(const char *file1, const char *file2) {
    // Dummy logic – in real use, replace with backend comparison
    if (!file1 || !file2 || strlen(file1) == 0 || strlen(file2) == 0)
        return 0.0;
    return 78.6; // Example percentage
}

// --- Button click handler ---
void on_check_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget **widgets = (GtkWidget **)user_data;
    GtkFileChooser *chooser1 = GTK_FILE_CHOOSER(widgets[0]);
    GtkFileChooser *chooser2 = GTK_FILE_CHOOSER(widgets[1]);
    GtkLabel *result_label = GTK_LABEL(widgets[2]);

    char *file1 = gtk_file_chooser_get_filename(chooser1);
    char *file2 = gtk_file_chooser_get_filename(chooser2);

    if (!file1 || !file2) {
        gtk_label_set_text(result_label, "⚠️ Please select both files!");
        return;
    }

    double similarity = check_plagiarism(file1, file2);
    char result_text[128];
    snprintf(result_text, sizeof(result_text), "Similarity: %.2f%%", similarity);
    gtk_label_set_text(result_label, result_text);

    g_free(file1);
    g_free(file2);
}

// --- Main ---
int main(int argc, char *argv[]) {
    GtkBuilder *builder;
    GtkWidget *window;
    GtkWidget *file_chooser1, *file_chooser2, *check_button, *result_label;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("interface.ui");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    file_chooser1 = GTK_WIDGET(gtk_builder_get_object(builder, "file_chooser1"));
    file_chooser2 = GTK_WIDGET(gtk_builder_get_object(builder, "file_chooser2"));
    check_button = GTK_WIDGET(gtk_builder_get_object(builder, "check_button"));
    result_label = GTK_WIDGET(gtk_builder_get_object(builder, "result_label"));

    GtkWidget *widgets[3] = { file_chooser1, file_chooser2, result_label };

    g_signal_connect(check_button, "clicked", G_CALLBACK(on_check_button_clicked), widgets);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
