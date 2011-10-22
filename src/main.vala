// compile me with
// valac --pkg gtk+-2.0 --pkg webkit-1.0 --thread webkit.vala

using Gtk;

int main (string[] args) {
  Gtk.init (ref args);

  var browser = new NBBrowser ();
  browser.start ();

  Gtk.main ();

  return 0;
}
