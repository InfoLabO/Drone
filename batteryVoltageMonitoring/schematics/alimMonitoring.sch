<Qucs Schematic 0.0.18>
<Properties>
  <View=43,3,757,409,1.5,20,0>
  <Grid=10,10,1>
  <DataSet=alimMonitoring.dat>
  <DataDisplay=alimMonitoring.dpl>
  <OpenDisplay=1>
  <Script=alimMonitoring.m>
  <RunScript=0>
  <showFrame=3>
  <FrameText0=Monitoring of drone battery>
  <FrameText1=Auteur : InfoLabO>
  <FrameText2=Date :11/05/2015>
  <FrameText3=Version :1.0>
</Properties>
<Symbol>
  <.PortSym 40 20 1 0>
  <.PortSym 40 60 2 0>
  <.PortSym 40 100 3 0>
</Symbol>
<Components>
  <GND * 1 250 330 0 0 0 0>
  <Vdc Battery 1 470 200 18 -26 0 1 "11.1 V" 1>
  <Port ArduinoAnalogPortA0 1 110 210 -23 12 0 0 "1" 1 "analog" 0>
  <Port DroneCircuitVcc 1 110 90 -23 12 0 0 "2" 1 "analog" 0>
  <Port DroneCircuitGround 1 110 330 -23 12 0 0 "3" 1 "analog" 0>
  <R R2 1 250 160 15 -26 0 1 "200 KOhm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <R R1 1 250 260 15 -26 0 1 "100 KOhm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <Eqn VoltageDivider 1 530 70 -23 14 0 0 "Vb=(R1/(R1+R2)) * Va = 1/3Va" 1 "yes" 0>
</Components>
<Wires>
  <470 90 470 170 "" 0 0 0 "">
  <250 90 470 90 "" 0 0 0 "">
  <250 90 250 130 "" 0 0 0 "">
  <250 190 250 210 "" 0 0 0 "">
  <250 290 250 330 "" 0 0 0 "">
  <250 330 470 330 "" 0 0 0 "">
  <470 230 470 330 "" 0 0 0 "">
  <250 210 250 230 "" 0 0 0 "">
  <110 210 250 210 "" 0 0 0 "">
  <110 90 250 90 "" 0 0 0 "">
  <110 330 250 330 "" 0 0 0 "">
  <250 90 250 90 "A" 280 60 0 "">
  <250 210 250 210 "B" 280 180 0 "">
</Wires>
<Diagrams>
</Diagrams>
<Paintings>
</Paintings>
