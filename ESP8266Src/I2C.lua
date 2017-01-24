i2c.setup(0, 1, 2, i2c.SLOW)

function read_reg_n(dev_addr, reg_addr, n)
    i2c.start(0)
    i2c.address(0, dev_addr, i2c.TRANSMITTER)
    i2c.write(0, reg_addr)
    i2c.stop(0)
    i2c.start(0)
    i2c.address(0, dev_addr, i2c.RECEIVER)
    local s = i2c.read(0, n)
    i2c.stop(0)
    return s
end

function read_reg(dev_addr, reg_addr)
    return string.byte(read_reg_n(dev_addr,reg_addr,1),1)
end

function read_regU16(dev_addr, reg_addr)
    local s = read_reg_n(dev_addr,reg_addr,2)
    return bit.lshift(string.byte(s,1),8)+string.byte(s,2)
end

function read_regU24(dev_addr, reg_addr)
    local s = read_reg_n(dev_addr,reg_addr,3)
    return bit.lshift(string.byte(s,1),16)+bit.lshift(string.byte(s,2),8)+string.byte(s,3)
end

function read_reg16(dev_addr, reg_addr)
    local c = read_regU16(dev_addr,reg_addr)
    if c>=32768 then c = c - 65536 end
    return c
end

function write_reg(dev_addr, reg_addr, reg_val)
    i2c.start(0)
    i2c.address(0, dev_addr, i2c.TRANSMITTER)
    i2c.write(0, reg_addr)
    i2c.write(0, reg_val)
    i2c.stop(0)
end
