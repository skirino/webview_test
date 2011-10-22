using Gtk;
using WebKit;

public class NBPane : VBox {

  private const string DEFAULT_PROTOCOL = "http";
  
  private Regex protocol_regex;
    private Entry url_bar;
    private WebView web_view;

    private ToolButton back_button;
    private ToolButton forward_button;
    private ToolButton reload_button;

    public signal void title_changed (WebView source, WebFrame frame, string title);
    
    
    public NBPane () {
      GLib.Object(homogeneous: false, spacing: 0);
      
      try {
        this.protocol_regex = new Regex (".*://.*");
      } catch (RegexError e) {
        critical ("%s", e.message);
      }
      
      init_children();

      connect_signals();
      this.url_bar.grab_focus();
    }
    
    private void init_children() {
      var toolbar = new Toolbar ();
      this.back_button = new ToolButton.from_stock (Stock.GO_BACK);
      this.forward_button = new ToolButton.from_stock (Stock.GO_FORWARD);
      this.reload_button = new ToolButton.from_stock (Stock.REFRESH);
      toolbar.add (this.back_button);
      toolbar.add (this.forward_button);
      toolbar.add (this.reload_button);

      this.url_bar = new Entry ();

      this.web_view = new WebView ();
      var scrolled_window = new ScrolledWindow (null, null);
      scrolled_window.set_policy (PolicyType.AUTOMATIC, PolicyType.AUTOMATIC);
      scrolled_window.add (this.web_view);
      
      this.pack_start (toolbar, false, true, 0);
      this.pack_start (this.url_bar, false, true, 0);
      this.add (scrolled_window);
    }
    
    private void connect_signals () {
        this.destroy.connect (Gtk.main_quit);
        this.url_bar.activate.connect (on_activate);
        this.web_view.title_changed.connect ((source, frame, title) => {
            this.title_changed(source, frame, title);
        });
        this.web_view.load_committed.connect (this.update_buttons);
        this.back_button.clicked.connect (this.web_view.go_back);
        this.forward_button.clicked.connect (this.web_view.go_forward);
        this.reload_button.clicked.connect (this.web_view.reload);
    }

    private void update_buttons (WebView source, WebFrame frame) {
      this.url_bar.text = frame.get_uri ();
      this.back_button.sensitive = this.web_view.can_go_back ();
      this.forward_button.sensitive = this.web_view.can_go_forward ();
    }
    
    
    private void on_activate () {
        var url = this.url_bar.text;
        if (!this.protocol_regex.match (url)) {
            url = "%s://%s".printf (NBPane.DEFAULT_PROTOCOL, url);
        }
        this.web_view.open (url);
    }

    public void open (string url) {
      this.web_view.open (url);
    }
}
