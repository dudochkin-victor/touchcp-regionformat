
desktop.files = data/share/applications/regionformat.desktop
desktop.path = $$DCP_DESKTOP_DIR
INSTALLS += desktop

style.files += data/share/themes/base/meegotouch/duicontrolpanel/style/regionformat.css
style.path = $$DCP_THEME_DIR/style
INSTALLS += style


regionconf.files = data/etc/$$REGION_CONF_FILENAME
regionconf.path = $$REGION_CONF_DIR
INSTALLS += regionconf
