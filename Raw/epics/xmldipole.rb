require 'socket'
require '/home/gamma16/epics_ori/epics_client'
require '/home/gamma16/epics_ori/bigrips.rb'

epics = EPICS_client.new('bripsrv.rarfadv.riken.go.jp',8500)
dipolename = ['D1','D2','D3','D4','D5','D6','D7','D8']
dipole = Array.new
dipolename.each {|name|
  dipole.push Dipole.new(name,epics)
}

print "<babild>\n <runstatus>\n";
dipole.each {|adipole|
  print "  <dipole>\n";
  print "   <name>",  adipole.name, "</name>\n";
  print "   <brho>", adipole.brho, "</brho>\n";
  print "   <nmr>",  adipole.nmr,  "</nmr>\n";
  print "  </dipole>\n";
}
print " </runstatus>\n</babild>\n";

epics.get("quit")
