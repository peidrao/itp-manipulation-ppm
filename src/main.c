/**
 * gcc src/edicao.c src/main.c -o bin/main -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
 * gcc src/edicao.c src/main.c -o bin/main -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic -Wall -ggdb
 **/

#include "edicao.h"

#include <gtk/gtk.h>

int executarSaveFileChooser();

GtkBuilder *builder;
GtkWidget *window;
GtkWidget *fixed;
GtkWidget *openImageLabel;
GtkWidget *imagePath;
GtkWidget *openImageErrorLabel;
GtkWidget *edicaoComboBox;
GtkWidget *levelEdicaoComboBox;
GtkWidget *levelEdicaoComboBoxEntry;
GtkWidget *nextButton;
GtkWidget *backButton;

Imagem imagem;
char *caminhoImagemSalvar;

int pagina = 0;
int edicaoSelecionada = -1;

int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);

  builder = gtk_builder_new_from_file("gtk-ui.glade");
  window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
  if (window == NULL) {
    printf("Não foi possível iniciar o programa\n");
  }

  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_builder_connect_signals(builder, NULL);

  fixed = GTK_WIDGET(gtk_builder_get_object(builder, "fixed"));
  openImageLabel = GTK_WIDGET(gtk_builder_get_object(builder, "openImageLabel"));
  imagePath = GTK_WIDGET(gtk_builder_get_object(builder, "imagePath"));
  openImageErrorLabel = GTK_WIDGET(gtk_builder_get_object(builder, "openImageErrorLabel"));
  edicaoComboBox = GTK_WIDGET(gtk_builder_get_object(builder, "edicaoComboBox"));
  levelEdicaoComboBox = GTK_WIDGET(gtk_builder_get_object(builder, "levelEdicaoComboBox"));
  levelEdicaoComboBoxEntry = GTK_WIDGET(gtk_builder_get_object(builder, "levelEdicaoComboBoxEntry"));
  nextButton = GTK_WIDGET(gtk_builder_get_object(builder, "nextButton"));
  backButton = GTK_WIDGET(gtk_builder_get_object(builder, "backButton"));

  gtk_widget_show(window);

  gtk_main();

  return EXIT_SUCCESS;
}

void executarEdicao(Edicao edicao, int nivel) {
  if (edicao == ESC) {
    filtroEscalaCinza(&imagem);
  } else if (edicao == AMP) {
    ampliar(&imagem, nivel);
  } else if (edicao == RED) {
    reduzir(&imagem, nivel);
  } else if (edicao == ROT) {
    for (int i = 0; i < nivel / 90; i++) {
      rotacionar(&imagem, nivel);
    }
  } else if(edicao == BLU) {
    float blurring[3][3] = {{1/9.0, 1/9.0, 1/9.0}, {1/9.0, 1/9.0, 1/9.0}, {1/9.0, 1/9.0, 1/9.0}};
    filtroMascara(&imagem, blurring);
  } else if(edicao == SHA) {
    float sharpening[3][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
    filtroMascara(&imagem, sharpening);
  } else if (edicao == DET) {
    if (nivel == 1) {
      float deteccaoBordas[3][3] = {{1, 0, -1}, {0, 0, 0}, {-1, 0, 1}};
      filtroMascara(&imagem, deteccaoBordas);
    } else if (nivel == 2) {
      float deteccaoBordas[3][3] = {{0, 1, 0}, {1, -4, 1}, {0, 1, 0}};
      filtroMascara(&imagem, deteccaoBordas);
    } else if (nivel == 3) {
      float deteccaoBordas[3][3] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
      filtroMascara(&imagem, deteccaoBordas);
    }
  } else if(edicao == THR) {
    filtroBinarizar(&imagem, nivel);
  } else if (edicao == NEG) {
    filtroNegativo(&imagem);
  } else if (edicao == PIX) {
    filtroPixelizar(&imagem);
  } else if (edicao == SOB) {
    filtroSobel(&imagem);
  } else if(edicao == GAU) {
    filtroGaussiano(&imagem);
  }
}

void setPage() {
  if (pagina == PAGINA_ESCOLHER_IMAGEM) {
    gtk_button_set_label(GTK_BUTTON(nextButton), "Continuar");

    gtk_widget_set_visible(nextButton, true);
    gtk_widget_set_visible(backButton, false);

    gtk_widget_set_sensitive(nextButton, true);

    gtk_widget_set_visible(edicaoComboBox, false);

    gtk_widget_set_visible(openImageLabel, true);
    gtk_widget_set_visible(imagePath, true);
    gtk_widget_set_visible(openImageErrorLabel, true);
  } else if (pagina == PAGINA_ESCOLHER_EDICAO) {
    gtk_button_set_label(GTK_BUTTON(nextButton), "Salvar");

    gtk_widget_set_visible(nextButton, true);
    gtk_widget_set_visible(backButton, true);

    if (edicaoSelecionada > -1) {
      gtk_widget_set_sensitive(nextButton, true);
    } else {
      gtk_widget_set_sensitive(nextButton, false);
    }

    gtk_widget_set_visible(openImageLabel, false);
    gtk_widget_set_visible(imagePath, false);
    gtk_widget_set_visible(openImageErrorLabel, false);

    gtk_widget_set_visible(edicaoComboBox, true);
  } else if (pagina == PAGINA_CONCLUIDO) {
    if (executarSaveFileChooser() == EXIT_SUCCESS) {
      int nivel = 0;
      if (gtk_widget_is_visible(levelEdicaoComboBox)) {
        sscanf(gtk_entry_get_text(GTK_ENTRY(levelEdicaoComboBoxEntry)), "%d", &nivel);
      }
      executarEdicao(edicaoSelecionada, nivel); // realiza a edição de imagem requerida
      
      gravarImagem(&imagem, caminhoImagemSalvar); // Após a imagem ser lida e o usuário escolher o filtro que será aplciada a mesma, essa função irá salvar a imagem em um arquivo modificado pelo filtro.
      gtk_widget_destroy(window);
    }
  }
}

void proximaPagina() {
  pagina++;
  setPage();
}

void anteriorPagina() {
  pagina--;
  setPage();
}

void executarOpenFileChooser() {
  GtkWidget *dialog;

  dialog = gtk_file_chooser_dialog_new("Selecione uma imagem .ppm", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, "gtk-cancel",
    GTK_RESPONSE_CANCEL, "gtk-open", GTK_RESPONSE_ACCEPT, NULL);
  gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));

  if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
    char *caminhoImagem;
    GtkFileChooser *fileChooser = GTK_FILE_CHOOSER(dialog);
    caminhoImagem = gtk_file_chooser_get_filename(fileChooser);
    gtk_entry_set_text(GTK_ENTRY(imagePath), caminhoImagem);

    char *erro;
    erro = lerImagem(&imagem, caminhoImagem); // Resposnsável por fazer toda a leitura da imagem e retornar erros de leitura

    gtk_label_set_text(GTK_LABEL(openImageErrorLabel), erro);

    if (erro == NULL) {
      gtk_widget_set_sensitive(nextButton, true);
    } else {
      gtk_widget_set_sensitive(nextButton, false);
    }

    g_free(caminhoImagem);
  }

  gtk_widget_destroy(dialog);
}

int executarSaveFileChooser() {
  GtkWidget *dialog;

  dialog = gtk_file_chooser_dialog_new("Escolha onde deseja salvar a imagem .ppm editada", NULL, GTK_FILE_CHOOSER_ACTION_SAVE,
    "gtk-cancel", GTK_RESPONSE_CANCEL, "gtk-save", GTK_RESPONSE_ACCEPT, NULL);
  gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER (dialog), TRUE);
  gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));
  gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), "imagem.ppm");

  if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
    caminhoImagemSalvar = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

    gtk_widget_destroy(dialog);
    return EXIT_SUCCESS;
  } else {
    anteriorPagina();

    gtk_widget_destroy(dialog);
    return EXIT_FAILURE;
  }
}

void on_imagePath_button_release_event() {
  executarOpenFileChooser();
}

void on_imagePath_icon_release() {
  executarOpenFileChooser();
}

void on_nextButton_clicked() {
  proximaPagina();
}

void on_backButton_clicked() {
  anteriorPagina();
}

void on_edicaoComboBox_changed(GtkComboBox *c) {
  edicaoSelecionada = gtk_combo_box_get_active(c);

  if (edicaoSelecionada == ESC || edicaoSelecionada == BLU || edicaoSelecionada == SHA || edicaoSelecionada == NEG ||
    edicaoSelecionada == PIX || edicaoSelecionada == SOB || edicaoSelecionada == GAU) {
    gtk_widget_set_visible(levelEdicaoComboBox, false);
    gtk_widget_set_sensitive(nextButton, true);
  } else {
    gtk_widget_set_sensitive(nextButton, false);

    int tipoLista = 0;
    if (edicaoSelecionada == AMP) {
      gtk_entry_set_placeholder_text(GTK_ENTRY(levelEdicaoComboBoxEntry), "Selecione a Ampliação");
    } else if (edicaoSelecionada == RED) {
      gtk_entry_set_placeholder_text(GTK_ENTRY(levelEdicaoComboBoxEntry), "Selecione a Redução");
    } else if (edicaoSelecionada == ROT) {
      tipoLista = 1;
      gtk_entry_set_placeholder_text(GTK_ENTRY(levelEdicaoComboBoxEntry), "Selecione a Rotação");
    } else if (edicaoSelecionada == DET) {
      gtk_entry_set_placeholder_text(GTK_ENTRY(levelEdicaoComboBoxEntry), "Selecione a Detecção de Bordas");
    } else if (edicaoSelecionada == THR) {
      gtk_entry_set_placeholder_text(GTK_ENTRY(levelEdicaoComboBoxEntry), "Selecione a Binarização");
    }

    if (tipoLista == 0) {
      gtk_combo_box_set_active(GTK_COMBO_BOX(levelEdicaoComboBox), 0);
      gtk_entry_set_text(GTK_ENTRY(levelEdicaoComboBoxEntry), "");
      gtk_combo_box_set_entry_text_column(GTK_COMBO_BOX(levelEdicaoComboBox), tipoLista);
      gtk_widget_set_visible(levelEdicaoComboBox, true);
    } else if (tipoLista == 1) {
      gtk_combo_box_set_active(GTK_COMBO_BOX(levelEdicaoComboBox), 0);
      gtk_entry_set_text(GTK_ENTRY(levelEdicaoComboBoxEntry), "");
      gtk_combo_box_set_entry_text_column(GTK_COMBO_BOX(levelEdicaoComboBox), tipoLista);
      gtk_widget_set_visible(levelEdicaoComboBox, true);
    }
  }
}

void on_levelEdicaoComboBox_changed() {
  if (strcmp(gtk_entry_get_text(GTK_ENTRY(levelEdicaoComboBoxEntry)), "") == 0) {
    gtk_widget_set_sensitive(nextButton, false);
  } else {
    gtk_widget_set_sensitive(nextButton, true);
  }
}

void on_imageSavePath_button_release_event() {
  executarSaveFileChooser();
}

void on_imageSavePath_icon_release() {
  executarSaveFileChooser();
}

void on_cancelButton_clicked() {
  gtk_widget_destroy(window);
}
