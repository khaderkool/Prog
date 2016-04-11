print "Hello world"

-- trivial protocol example
-- declare our protocol
trivial_proto = Proto("tri","tri_proto")

-- create a function to dissect it
function trivial_proto.dissector(buffer,pinfo,tree)

    pinfo.cols.protocol = "tri" --sets Protocol on wireshark
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
		
	local subtree = tree:add(trivial_proto,buffer()) 
	
	--tell packet type & request type --> this will go on info session in wireshar UI
	-- this will add 'req ping' or 'resp ping' pinfo.cols.info = string.format('%s %s', tpak_type[packet_type], treq_type[req_type])
	
	
	--construct data parser
	
	pinfo.cols.info = string.format('%s', tpak_type[packet_type])
	--subtree:add(trivial_proto.fields.bytes, buffer(0,1),buffer(0,1):uint() .. ": " .. tpak_type[packet_type])
	subtree:add(f_bytes, buffer(0,1), tpak_type[packet_type])
	subtree:add(buffer(1,1),treq_type[req_type])
	
	if buffer:len() > 2 then
	  subtree:add(trivial_proto.fields.string, buffer(3,pay_load_len), buffer(3,pay_load_len):string())
	end
	
	
end

-- load the udp.port table
udp_table = DissectorTable.get("udp.port")
udp_table:add(3333,trivial_proto)

f_bytes = ProtoField.string("tri.data", "bytes")

trivial_proto.fields.u16 = ProtoField.int16("tri.length", "Length", base.DEC)
f_bytes = ProtoField.string("tri.data", "data") 
trivial_proto.fields.string = ProtoField.string("tri.payload", "Data") 
trivial_proto.fields = {f_bytes}



