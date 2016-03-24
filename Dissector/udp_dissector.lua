print "Hello world"

-- trivial protocol example
-- declare our protocol
trivial_proto = Proto("trivial","Trivial Protocol")
-- create a function to dissect it
function trivial_proto.dissector(buffer,pinfo,tree)
    pinfo.cols.protocol = "TRIVIAL-3" --sets Protocol on wireshark
	if buffer:len() < 2 then
	  return -- must have atleast 2 bytes of data to parse
	end
	
    --read packet
	local packet_type = buffer(0,1):uint() -- 0 - req; 1 - resp
	local req_type = buffer(1,1):uint() -- as of now 1-ping
	local pay_load_len = 0 
	local pay_load = nil 
	
	if buffer:len() > 2 then
	  pay_load_len = buffer(2,1):uint() -- payload len if any
	  payload = buffer(3, pay_load_len):string() -- payload
	end
	--get default table
	local tpak_type = { [0] = "req", [1] = "resp" } 
	local treq_type = { [1] = "ping", [2] = "time" }
		
	local subtree = tree:add(trivial_proto,buffer(),"Trivial Protocol Data") --sets Data name
	
	--tell packet type & request type --> this will go on info session in wireshar UI
	-- this will add 'req ping' or 'resp ping' pinfo.cols.info = string.format('%s %s', tpak_type[packet_type], treq_type[req_type])
	pinfo.cols.info = string.format('%s', tpak_type[packet_type])
	
	--construct data parser
	subtree:add(buffer(0,1),buffer(0,1):uint() .. ": " .. tpak_type[packet_type])
	subtree:add(buffer(1,1),buffer(1,1):uint() .. ": ".. treq_type[req_type])
	
	if buffer:len() > 2 then
	  --subtree:add(buffer(2,1),"Payload len:  ".. buffer(2,1):uint())
	  --subtree:add(buffer(2,1),"Payload:  ".. buffer(3,pay_load_len):string())
	  subtree:add(buffer(2,1),"Payload len:  ".. pay_load_len)
	  subtree:add(buffer(2,1),"Payload:  ".. payload)
	end
	
	
end
-- load the udp.port table
udp_table = DissectorTable.get("udp.port")
-- register our protocol to handle udp port 7777
udp_table:add(3333,trivial_proto)