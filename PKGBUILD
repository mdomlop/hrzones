# Maintainer: Manuel Domínguez López <mdomlop at gmail dot com>

_pkgver_year=2021
_pkgver_month=07
_pkgver_day=24

pkgname=hrzones
pkgver=0.10a
pkgrel=1
pkgdesc='Calculate heart rate training zones, based on Karvonen formula.'
arch=('i686' 'x86_64')
url="https://github.com/mdomlop/$pkgname"
source=()
license=('GPL3')

build() {
    cd $startdir
    make
    }

package() {
    cd $startdir
    make install DESTDIR=$pkgdir
}
