%{!?qtc_qmake:%define qtc_qmake %qmake}
%{!?qtc_qmake5:%define qtc_qmake5 %qmake5}
%{!?qtc_make:%define qtc_make make}
%{?qtc_builddir:%define _builddir %qtc_builddir}

Name:       glacier-music
Summary:    Glacier music player
Version:    0.2
Release:    1
Group:      Application/Media
License:    LGPL
URL:        https://github.com/nemomobile-ux/glacier-music
Source0:    %{name}-%{version}.tar.bz2
Requires:   qt5-qtquickcontrols-nemo
Requires:   taglib >= 1.11.1
Requires:   nemo-qml-plugin-settings
Requires:   mpris-qt5-qml-plugin
Requires:   libglacierapp
Requires:   mapplauncherd-booster-nemomobile
Requires:   qt5-qtmultimedia-plugin-mediaservice-gstmediaplayer

BuildRequires:  cmake
BuildRequires:  pkgconfig(taglib) >= 1.11.1
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  pkgconfig(Qt5Multimedia)
BuildRequires:  pkgconfig(glacierapp)
BuildRequires:  desktop-file-utils

%description
Music application for nemo mobile

%prep
%setup -q -n %{name}-%{version}

%build
mkdir build
cd build
cmake \
	-DCMAKE_BUILD_TYPE=Release \
	-DCMAKE_INSTALL_PREFIX=%{_prefix} \	
	-DCMAKE_VERBOSE_MAKEFILE=ON \
	..
cmake --build .

%install
cd build
rm -rf %{buildroot}
DESTDIR=%{buildroot} cmake --build . --target install

%files
%defattr(-,root,root,-)
%{_bindir}
%{_datadir}/%{name}
%{_datadir}/applications/%{name}.desktop
