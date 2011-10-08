
#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <webkit/webkit.h>
#include <stdlib.h>
#include <string.h>


#define TYPE_GENIE_BROWSER (genie_browser_get_type ())
#define GENIE_BROWSER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_GENIE_BROWSER, GenieBrowser))
#define GENIE_BROWSER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_GENIE_BROWSER, GenieBrowserClass))
#define IS_GENIE_BROWSER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_GENIE_BROWSER))
#define IS_GENIE_BROWSER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_GENIE_BROWSER))
#define GENIE_BROWSER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_GENIE_BROWSER, GenieBrowserClass))

typedef struct _GenieBrowser GenieBrowser;
typedef struct _GenieBrowserClass GenieBrowserClass;
typedef struct _GenieBrowserPrivate GenieBrowserPrivate;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))

struct _GenieBrowser {
	GtkWindow parent_instance;
	GenieBrowserPrivate * priv;
	WebKitWebView* web_view;
};

struct _GenieBrowserClass {
	GtkWindowClass parent_class;
};


static gpointer genie_browser_parent_class = NULL;

GType genie_browser_get_type (void);
enum  {
	GENIE_BROWSER_DUMMY_PROPERTY
};
void genie_browser_create_widgets (GenieBrowser* self);
GenieBrowser* genie_browser_new (gint a);
GenieBrowser* genie_browser_construct (GType object_type, gint a);
static void genie_browser_finalize (GObject* obj);
static void _gtk_main_quit_gtk_object_destroy (GtkObject* _sender, gpointer self);
void _main (char** args, int args_length1);



GenieBrowser* genie_browser_construct (GType object_type, gint a) {
	GenieBrowser * self;
	self = g_object_newv (object_type, 0, NULL);
	gtk_window_set_default_size ((GtkWindow*) self, 800, 600);
	genie_browser_create_widgets (self);
	return self;
}


GenieBrowser* genie_browser_new (gint a) {
	return genie_browser_construct (TYPE_GENIE_BROWSER, a);
}


void genie_browser_create_widgets (GenieBrowser* self) {
	WebKitWebView* _tmp0_;
	GtkScrolledWindow* scrolled_window;
	g_return_if_fail (self != NULL);
	self->web_view = (_tmp0_ = g_object_ref_sink ((WebKitWebView*) webkit_web_view_new ()), _g_object_unref0 (self->web_view), _tmp0_);
	webkit_web_view_open (self->web_view, "http://www.google.co.jp/");
	scrolled_window = g_object_ref_sink ((GtkScrolledWindow*) gtk_scrolled_window_new (NULL, NULL));
	gtk_scrolled_window_set_policy (scrolled_window, GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_container_add ((GtkContainer*) scrolled_window, (GtkWidget*) self->web_view);
	gtk_container_add ((GtkContainer*) self, (GtkWidget*) scrolled_window);
	_g_object_unref0 (scrolled_window);
}


static void genie_browser_class_init (GenieBrowserClass * klass) {
	genie_browser_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = genie_browser_finalize;
}


static void genie_browser_instance_init (GenieBrowser * self) {
}


static void genie_browser_finalize (GObject* obj) {
	GenieBrowser * self;
	self = GENIE_BROWSER (obj);
	_g_object_unref0 (self->web_view);
	G_OBJECT_CLASS (genie_browser_parent_class)->finalize (obj);
}


GType genie_browser_get_type (void) {
	static GType genie_browser_type_id = 0;
	if (genie_browser_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GenieBrowserClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) genie_browser_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GenieBrowser), 0, (GInstanceInitFunc) genie_browser_instance_init, NULL };
		genie_browser_type_id = g_type_register_static (GTK_TYPE_WINDOW, "GenieBrowser", &g_define_type_info, 0);
	}
	return genie_browser_type_id;
}


static void _gtk_main_quit_gtk_object_destroy (GtkObject* _sender, gpointer self) {
	gtk_main_quit ();
}


void _main (char** args, int args_length1) {
	GenieBrowser* win;
	gtk_init (&args_length1, &args);
	win = g_object_ref_sink (genie_browser_new (0));
	gtk_widget_show_all ((GtkWidget*) win);
	g_signal_connect ((GtkObject*) win, "destroy", (GCallback) _gtk_main_quit_gtk_object_destroy, NULL);
	gtk_main ();
	_g_object_unref0 (win);
}


int main (int argc, char ** argv) {
	g_thread_init (NULL);
	g_type_init ();
	_main (argv, argc);
	return 0;
}




