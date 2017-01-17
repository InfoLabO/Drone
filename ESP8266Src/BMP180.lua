-- Presure temperature sensor adress = 0x77

AC1 = 0
AC2 = 0
AC3 = 0
AC4 = 0
AC5 = 0
AC6 = 0
B1  = 0
B2  = 0
MB  = 0
MC  = 0
MD = 0
B5 = 0

function bmp180_ld_reg()
	AC1 = read_reg16(0x77,0xAA)
	AC2 = read_reg16(0x77,0xAC)
	AC3 = read_reg16(0x77,0xAE)
	AC4 = read_regU16(0x77,0xB0)
	AC5 = read_regU16(0x77,0xB2)
	AC6 = read_regU16(0x77,0xB4)
	B1  = read_reg16(0x77,0xB6)
	B2  = read_reg16(0x77,0xB8)
	MB  = read_reg16(0x77,0xBA)
	MC  = read_reg16(0x77,0xBC)
	MD = read_reg16(0x77,0xBE)
end

function bmp180_rdToc_reg()
	write_reg(0x77,0xF4,0x2E)
	tmr.delay(5000)
	local UT = read_reg16(0x77,0xF6)
	local X1 = ((UT-AC6)*AC5)/32768
	local X2 = MC*2048/(X1+MD)
	B5=X1+X2
	return (B5+8)/160
end

function bmp180_rdPres_reg(oss)
	write_reg(0x77,0xF4,0x34+bit.lshift(oss,6))
	if oss==0 then tmr.delay(5000) end
	if oss==1 then tmr.delay(8000) end
	if oss==2 then tmr.delay(14000) end
	if oss==3 then tmr.delay(26000) end
	local UP = bit.rshift(read_regU24(0x77,0xF6),(8-oss))
	local B6 = B5-4000
	local X1 = (B2*(B6*B6/4096))/2048
	local X2 = (AC2*B6)/2048
	local X3 = X1+X2
	local B3 = ((AC1*4+X3)*bit.lshift(1,oss)+2)/4
	X1 = (AC3*B6)/8192
	X2 = (B1*((B6*B6)/4096))/65536
	X3 = ((X1+X2)+2)/4
	local B4 = (AC4*(X3+32768))/32768
	local B7 = (UP-B3)*bit.rshift(50000,oss)
	local p = 0
	if B7<0x80000000 then p=(B7*2)/B4 else p=(B7/B4)*2 end
	X1 = (p/256)*(p/256)
	X1 = (X1*3038)/65536
	X2 = (-7357*p)/65536
	return p+(X1+X2+3791)/16
end

function bmp180_calc_alt(sealvlp,rdlvlp)
    return 44330*(1.0-math.pow(rdlvlp/sealvlp,0.1903))
end

