class STQ
  def initialize(name,epics)
    @name = name.to_s
    @epics = epics
  end
  def brho
    channel = "psld:" + @name + ":Brho"
    value = sprintf("%#10.4f",@epics.get(channel).to_f)
    return value
  end
  def curinp
    channel = "psld:" + @name + ":curinp"
    value = sprintf("%#10.4f",@epics.get(channel).to_f)
    return value
  end
  def cnvcur
    channel = "psld:" + @name + ":cnvcur"
    value = sprintf("%#10.4f",@epics.get(channel).to_f)
    return value
  end
  def status
    channel = "psld:" + @name + ":errstat"
    value = @epics.get(channel).to_i
    return value
  end
  def spole
    channel = "psld:" + @name + ":status.B7"
    value = @epics.get(channel).to_i
    return value
  end
  attr_reader :name
end
class Dipole
  def initialize(name,epics)
    @name = name.to_s
    @epics = epics
  end
  def nmr
    channel = "nmr:" + @name
    value = @epics.get(channel)
    return value
  end
  def brho
    channel = "psld:" + @name + ":Brho"
    value = sprintf("%#.4f",@epics.get(channel).to_f)
    return value
  end
  def curinp
    channel = "psld:" + @name + ":curinp"
    value = sprintf("%#.4f",@epics.get(channel).to_f)
    return value
  end
  def cnvcur
    channel = "psld:" + @name + ":cnvcur"
    value = sprintf("%#.4f",@epics.get(channel).to_f)
    return value
  end
  attr_reader :name
end

class Chamber
  def initialize(focalname)
    @focalname = focalname
  end
  def ppac(num)
    channel = "slit:" + @focalname + "ppac" + num.to_s + ":inst"
    value = @epics.get(channel)
  end
  def pla()
    channel = "slit:" + @focalname + "plastic:inst"
    value = @epics.get(channel)
  end
  def slit2dl()
    channel = "slit:" + @focalname + "2dl:pos1"
    value = @epics.get(channel)
  end
  def slit2dr()
    channel = "slit:" + @focalname + "2dr:pos1"
    value = @epics.get(channel)
  end
end
