class EPICS_client
  def initialize(hostname,port)
    begin
      @conn = TCPSocket.new(hostname,port)
      return 0
    rescue SoketError => errormessage
      puts "Connection Error\n"
      puts errormessage
    end
  end
  def get(channel)
    string = channel + "\n" if channel != nil
    @conn.write(string)
    rvalue = @conn.gets.chop
    return rvalue
  end
  def get_line(channel)
    @array = Array.new
    string = channel + "\n" if channel != nil
    @conn.write(string)
    while (rvalue = @conn.gets) do
      break if rvalue.chop.to_s == "end"
      @array.push rvalue
    end
    return @array
  end
end
