require 'socket'
require 'epics_client'
require 'bigrips.rb'

epics = EPICS_client.new('bripsrv.rarfadv.riken.go.jp',8500)
dipolename = ['D1','D2','D3','D4','D5','D6','D7','D8']
dipole = Array.new
dipolename.each {|name|
  dipole.push Dipole.new(name,epics)
}
dipole.each {|adipole|
  print adipole.name,',',adipole.brho,',',adipole.nmr,"\n"
}
array = epics.get_line("chamber")
array.each {|aarray|
print aarray 
}
epics.get("quit")
