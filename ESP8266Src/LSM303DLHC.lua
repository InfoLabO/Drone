-- Accel sensor adress = 0x19
-- Add 0x08 to the reg adresse to get the auto increment

function lsm303dlhc_setRefRate(refrate)
	write_reg(0x19,0x20,0x07+bit.lshift(refrate,4))
end

function lsm303dlhc_getRawAccelXYZ()
	local s = read_reg_n(0x19,0xA8,6);
	local x = s:byte(1) + bit.lshift(s:byte(2),8)
	local y = s:byte(3) + bit.lshift(s:byte(4),8)
	local z = s:byte(5) + bit.lshift(s:byte(6),8)
	if x>32768 then x = x  - 65536 end
	if y>32768 then y = y  - 65536 end
	if z>32768 then z = z  - 65536 end
    return x,y,z;
end

function lsm303dlhc_getRawMagnXYZ()
	local s = read_reg_n(0x19,0x83,6);
	local x = s:byte(2) + bit.lshift(s:byte(1),8)
	local y = s:byte(6) + bit.lshift(s:byte(5),8)
	local z = s:byte(4) + bit.lshift(s:byte(3),8)
	if x>32768 then x = x  - 65536 end
	if y>32768 then y = y  - 65536 end
	if z>32768 then z = z  - 65536 end
    return x,y,z;
end
