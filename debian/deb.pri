BP_BIN=dpkg-buildpackage
FAKEROOT_BIN=fakeroot

changelog.target = changelog
changelog.depends += FORCE
changelog.commands = ./debian/updatechangelog


deb.target = deb
!isEmpty(BP_BIN) {
    !isEmpty(FAKEROOT_BIN) {
        deb.commands = $${BP_BIN} -rfakeroot  -b
    } else {
        deb.commands = @echo "Unable to detect fakeroot in PATH"
    }
} else {
    deb.commands = @echo "Unable to detect dpkg-buildpackage in PATH"
}
deb.depends = changelog
deb.depends = FORCE


QMAKE_EXTRA_UNIX_TARGETS += deb 
QMAKE_EXTRA_UNIX_TARGETS += changelog
