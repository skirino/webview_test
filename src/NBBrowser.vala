using Gtk;
using WebKit;

public class NBBrowser : Window {
  
  private const string TITLE = "NetBehind Browser";
    private const string HOME_URL = "http://www.google.co.jp/";
    private Label status_bar;
    private NBPane pane;

    public NBBrowser () {
        this.title = NBBrowser.TITLE;
        set_default_size (800, 600);

        create_widgets ();
        show_all ();
    }

    private void create_widgets () {
        this.status_bar = new Label ("Welcome");
        this.status_bar.xalign = 0;
        var vbox = new VBox (false, 0);
        
        this.pane = new NBPane();
        this.pane.title_changed.connect ((source, frame, title) => {
            this.title = "%s - %s".printf (title, NBBrowser.TITLE);
        });

        vbox.add(this.pane);
        
        vbox.pack_start (this.status_bar, false, true, 0);
        add (vbox);
    }
    
    public void start () {
      this.pane.open(HOME_URL);
    }
}
