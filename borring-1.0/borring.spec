Name:           borring
Version:        1.0 
Release:        1%{?dist}
Summary:        A borring program

License:        GPLv3+
URL:            http://www.3m.com
Source0:        borring-1.0.tar.gz

Requires(post): info
Requires(preun): info

%description 
A borring program from the borring world

%prep
%setup

%build
make PREFIX=/usr %{?_smp_mflags}

%install
make PREFIX=/usr DESTDIR=%{?buildroot} install

%clean
rm -rf %{buildroot}

%files
%{_bindir}/borring
