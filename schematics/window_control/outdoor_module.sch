<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.6.2">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="4" name="Route4" color="1" fill="4" visible="no" active="no"/>
<layer number="5" name="Route5" color="4" fill="4" visible="no" active="no"/>
<layer number="6" name="Route6" color="1" fill="8" visible="no" active="no"/>
<layer number="7" name="Route7" color="4" fill="8" visible="no" active="no"/>
<layer number="8" name="Route8" color="1" fill="2" visible="no" active="no"/>
<layer number="9" name="Route9" color="4" fill="2" visible="no" active="no"/>
<layer number="10" name="Route10" color="1" fill="7" visible="no" active="no"/>
<layer number="11" name="Route11" color="4" fill="7" visible="no" active="no"/>
<layer number="12" name="Route12" color="1" fill="5" visible="no" active="no"/>
<layer number="13" name="Route13" color="4" fill="5" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="24" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="99" name="SpiceOrder" color="7" fill="1" visible="yes" active="yes"/>
<layer number="101" name="Hidden" color="15" fill="1" visible="yes" active="yes"/>
<layer number="102" name="Changes" color="12" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="my_devices">
<packages>
<package name="R">
<pad name="P$1" x="-6.35" y="0" drill="0.8" shape="square"/>
<pad name="P$2" x="6.35" y="0" drill="0.8" shape="square"/>
<wire x1="-3.81" y1="1.27" x2="-3.81" y2="0" width="0.127" layer="21"/>
<wire x1="-3.81" y1="0" x2="-3.81" y2="-1.27" width="0.127" layer="21"/>
<wire x1="-3.81" y1="-1.27" x2="3.81" y2="-1.27" width="0.127" layer="21"/>
<wire x1="3.81" y1="1.27" x2="-3.81" y2="1.27" width="0.127" layer="21"/>
<wire x1="-6.35" y1="0" x2="-3.81" y2="0" width="0.127" layer="21"/>
<wire x1="3.81" y1="1.27" x2="3.81" y2="0" width="0.127" layer="21"/>
<wire x1="3.81" y1="-1.27" x2="3.81" y2="0" width="0.127" layer="21"/>
<wire x1="3.81" y1="0" x2="6.35" y2="0" width="0.127" layer="21"/>
</package>
<package name="C">
<pad name="PIN_PLUS" x="-2.54" y="0" drill="0.8" shape="square"/>
<pad name="PIN_GND" x="2.54" y="0" drill="0.8" shape="square"/>
<circle x="0" y="0" radius="5.08" width="0.127" layer="21"/>
<wire x1="-3.175" y1="-1.905" x2="-1.905" y2="-1.905" width="0.127" layer="21"/>
<wire x1="-2.54" y1="-1.27" x2="-2.54" y2="-2.54" width="0.127" layer="21"/>
<wire x1="1.905" y1="-1.905" x2="3.175" y2="-1.905" width="0.127" layer="21"/>
</package>
<package name="BME280">
<pad name="GND" x="-5.08" y="1.27" drill="0.8" shape="square"/>
<pad name="SCL" x="-5.08" y="-1.27" drill="0.8" shape="square"/>
<pad name="VCC" x="-5.08" y="3.81" drill="0.8" shape="square"/>
<pad name="SDA" x="-5.08" y="-3.81" drill="0.8" shape="square"/>
<wire x1="-6.35" y1="5.08" x2="-6.35" y2="-10.16" width="0.127" layer="21"/>
<text x="-3.81" y="3.81" size="0.8128" layer="21">VCC</text>
<text x="-3.81" y="1.27" size="0.8128" layer="21">GND</text>
<text x="-3.81" y="-1.27" size="0.8128" layer="21">SCL</text>
<text x="-3.81" y="-3.81" size="0.8128" layer="21">SDA</text>
<wire x1="-6.35" y1="5.08" x2="2.54" y2="5.08" width="0.127" layer="21"/>
<wire x1="2.54" y1="5.08" x2="2.54" y2="-10.16" width="0.127" layer="21"/>
<wire x1="2.54" y1="-10.16" x2="-6.35" y2="-10.16" width="0.127" layer="21"/>
<text x="-5.08" y="-7.62" size="1.27" layer="21">BME280</text>
</package>
<package name="GY-SGP30">
<pad name="VIN" x="0" y="3.81" drill="0.8" shape="square"/>
<pad name="GND" x="0" y="1.27" drill="0.8" shape="square"/>
<pad name="SCL" x="0" y="-1.27" drill="0.8" shape="square"/>
<pad name="SDA" x="0" y="-3.81" drill="0.8" shape="square"/>
<wire x1="-1.27" y1="5.08" x2="-1.27" y2="-5.08" width="0.127" layer="21"/>
<wire x1="-1.27" y1="-5.08" x2="7.62" y2="-5.08" width="0.127" layer="21"/>
<text x="1.27" y="3.81" size="0.6096" layer="21">VIN</text>
<text x="1.27" y="1.27" size="0.6096" layer="21">GND</text>
<text x="1.27" y="-1.27" size="0.6096" layer="21">SCL</text>
<text x="1.27" y="-3.81" size="0.6096" layer="21">SDA</text>
<wire x1="7.62" y1="5.08" x2="-1.27" y2="5.08" width="0.127" layer="21"/>
<wire x1="7.62" y1="5.08" x2="7.62" y2="-5.08" width="0.127" layer="21"/>
<text x="5.08" y="-2.54" size="0.8128" layer="21" rot="R90">GY-SGP30</text>
</package>
<package name="C-1">
<pad name="P$1" x="-2.54" y="0" drill="0.8" shape="square"/>
<pad name="P$2" x="2.54" y="0" drill="0.8" shape="square"/>
<wire x1="-3.81" y1="1.27" x2="-3.81" y2="-1.27" width="0.127" layer="21"/>
<wire x1="-3.81" y1="-1.27" x2="3.81" y2="-1.27" width="0.127" layer="21"/>
<wire x1="3.81" y1="-1.27" x2="3.81" y2="1.27" width="0.127" layer="21"/>
<wire x1="3.81" y1="1.27" x2="-3.81" y2="1.27" width="0.127" layer="21"/>
<wire x1="-1.778" y1="0" x2="-0.254" y2="0" width="0.127" layer="21"/>
<wire x1="-0.254" y1="0" x2="-0.254" y2="0.508" width="0.127" layer="21"/>
<wire x1="-0.254" y1="0" x2="-0.254" y2="-0.508" width="0.127" layer="21"/>
<wire x1="0.254" y1="0.508" x2="0.254" y2="0" width="0.127" layer="21"/>
<wire x1="0.254" y1="0" x2="0.254" y2="-0.508" width="0.127" layer="21"/>
<wire x1="0.254" y1="0" x2="1.778" y2="0" width="0.127" layer="21"/>
</package>
<package name="RD-3362H">
<pad name="P1" x="-2.54" y="-1.27" drill="0.6" shape="square"/>
<pad name="P3" x="0" y="1.27" drill="0.6" shape="square"/>
<pad name="P2" x="2.54" y="-1.27" drill="0.6" shape="square"/>
<wire x1="-3.81" y1="3.81" x2="-3.81" y2="-3.81" width="0.127" layer="21"/>
<wire x1="3.81" y1="-3.81" x2="3.81" y2="3.81" width="0.127" layer="21"/>
<wire x1="-3.81" y1="-3.81" x2="3.81" y2="-3.81" width="0.127" layer="21"/>
<wire x1="-3.81" y1="3.81" x2="3.81" y2="3.81" width="0.127" layer="21"/>
</package>
<package name="RD-3296Z">
<pad name="P3" x="0" y="2.54" drill="0.8" shape="square"/>
<pad name="P1" x="-2.54" y="0" drill="0.8" shape="square"/>
<pad name="P2" x="2.54" y="0" drill="0.8" shape="square"/>
<wire x1="-5.08" y1="-1.27" x2="5.08" y2="-1.27" width="0.127" layer="21"/>
<wire x1="5.08" y1="-1.27" x2="5.08" y2="2.54" width="0.127" layer="21"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="3.81" width="0.127" layer="21"/>
<wire x1="5.08" y1="3.81" x2="-5.08" y2="3.81" width="0.127" layer="21"/>
<wire x1="-5.08" y1="3.81" x2="-5.08" y2="-1.27" width="0.127" layer="21"/>
<wire x1="5.08" y1="3.81" x2="6.35" y2="3.81" width="0.127" layer="21"/>
<wire x1="6.35" y1="3.81" x2="6.35" y2="2.54" width="0.127" layer="21"/>
<wire x1="6.35" y1="2.54" x2="5.08" y2="2.54" width="0.127" layer="21"/>
</package>
<package name="L-RLB0914">
<pad name="P$1" x="2.54" y="0" drill="0.8" shape="square"/>
<pad name="P$2" x="-2.54" y="0" drill="0.8" shape="square"/>
<circle x="0" y="0" radius="5.08" width="0.127" layer="21"/>
</package>
<package name="L-EC24">
<pad name="P$1" x="-7.62" y="0" drill="0.8" shape="square"/>
<pad name="P$2" x="7.62" y="0" drill="0.8" shape="square"/>
<wire x1="-7.62" y1="0" x2="-5.08" y2="0" width="0.127" layer="21"/>
<wire x1="7.62" y1="0" x2="5.08" y2="0" width="0.127" layer="21"/>
<wire x1="-5.08" y1="0" x2="-2.54" y2="0" width="0.127" layer="21" curve="-180"/>
<wire x1="-2.54" y1="0" x2="0" y2="0" width="0.127" layer="21" curve="-180"/>
<wire x1="0" y1="0" x2="2.54" y2="0" width="0.127" layer="21" curve="-180"/>
<wire x1="2.54" y1="0" x2="5.08" y2="0" width="0.127" layer="21" curve="-180"/>
</package>
<package name="MICROPHONE">
<pad name="P$1" x="-1.27" y="0" drill="0.9" shape="square"/>
<pad name="P$2" x="1.27" y="0" drill="0.9" shape="square"/>
<wire x1="-2.54" y1="1.27" x2="-2.54" y2="-1.27" width="0.127" layer="21"/>
<wire x1="-2.54" y1="-1.27" x2="2.54" y2="-1.27" width="0.127" layer="21"/>
<wire x1="2.54" y1="-1.27" x2="2.54" y2="1.27" width="0.127" layer="21"/>
<wire x1="2.54" y1="1.27" x2="-2.54" y2="1.27" width="0.127" layer="21"/>
</package>
<package name="DIP8">
<pad name="PIN_4" x="-3.81" y="-3.81" drill="0.8" shape="square"/>
<pad name="PIN_3" x="-3.81" y="-1.27" drill="0.8" shape="square"/>
<pad name="PIN_2" x="-3.81" y="1.27" drill="0.8" shape="square"/>
<pad name="PIN_1" x="-3.81" y="3.81" drill="0.8" shape="square"/>
<pad name="PIN_8" x="3.81" y="3.81" drill="0.8" shape="square"/>
<pad name="PIN_7" x="3.81" y="1.27" drill="0.8" shape="square"/>
<pad name="PIN_6" x="3.81" y="-1.27" drill="0.8" shape="square"/>
<pad name="PIN_5" x="3.81" y="-3.81" drill="0.8" shape="square"/>
<wire x1="-5.08" y1="-5.08" x2="5.08" y2="-5.08" width="0.127" layer="21"/>
<wire x1="5.08" y1="5.08" x2="0.635" y2="5.08" width="0.127" layer="21"/>
<wire x1="0.635" y1="5.08" x2="-0.635" y2="5.08" width="0.127" layer="21"/>
<wire x1="-0.635" y1="5.08" x2="-5.08" y2="5.08" width="0.127" layer="21"/>
<wire x1="-0.635" y1="5.08" x2="-0.635" y2="3.81" width="0.127" layer="21"/>
<wire x1="-0.635" y1="3.81" x2="0.635" y2="3.81" width="0.127" layer="21"/>
<wire x1="0.635" y1="3.81" x2="0.635" y2="5.08" width="0.127" layer="21"/>
<wire x1="-5.08" y1="5.08" x2="-5.08" y2="-5.08" width="0.127" layer="21"/>
<wire x1="5.08" y1="-5.08" x2="5.08" y2="5.08" width="0.127" layer="21"/>
</package>
<package name="VOLTAGE_REGULATOR">
<pad name="IN" x="-2.54" y="0" drill="0.6" shape="square"/>
<pad name="GND" x="0" y="0" drill="0.6" shape="square"/>
<pad name="OUT" x="2.54" y="0" drill="0.6" shape="square"/>
<wire x1="-5.08" y1="2.54" x2="-5.08" y2="-2.54" width="0.127" layer="21"/>
<wire x1="-5.08" y1="-2.54" x2="5.08" y2="-2.54" width="0.127" layer="21"/>
<wire x1="5.08" y1="-2.54" x2="5.08" y2="2.54" width="0.127" layer="21"/>
<wire x1="5.08" y1="2.54" x2="-5.08" y2="2.54" width="0.127" layer="21"/>
<text x="-3.81" y="1.27" size="0.6096" layer="21">in</text>
<text x="-1.27" y="1.27" size="0.6096" layer="21">gnd</text>
<text x="2.54" y="1.27" size="0.6096" layer="21">out</text>
</package>
<package name="ATMEGA328P">
<pad name="VCC" x="-3.81" y="0" drill="1" shape="square"/>
<pad name="GND" x="-3.81" y="-2.54" drill="1" shape="square"/>
<pad name="PD4" x="-3.81" y="2.54" drill="1" shape="square"/>
<pad name="PB6" x="-3.81" y="-5.08" drill="1" shape="square"/>
<pad name="PD3" x="-3.81" y="5.08" drill="1" shape="square"/>
<pad name="PB7" x="-3.81" y="-7.62" drill="1" shape="square"/>
<pad name="PD2" x="-3.81" y="7.62" drill="1" shape="square"/>
<pad name="PD5" x="-3.81" y="-10.16" drill="1" shape="square"/>
<pad name="PD1" x="-3.81" y="10.16" drill="1" shape="square"/>
<pad name="PD6" x="-3.81" y="-12.7" drill="1" shape="square"/>
<pad name="PD0" x="-3.81" y="12.7" drill="1" shape="square"/>
<pad name="PD7" x="-3.81" y="-15.24" drill="1" shape="square"/>
<pad name="PC6" x="-3.81" y="15.24" drill="1" shape="square"/>
<pad name="PB0" x="-3.81" y="-17.78" drill="1" shape="square"/>
<pad name="PB1" x="3.81" y="-17.78" drill="1" shape="square"/>
<pad name="PB2" x="3.81" y="-15.24" drill="1" shape="square"/>
<pad name="PB3" x="3.81" y="-12.7" drill="1" shape="square"/>
<pad name="PB4" x="3.81" y="-10.16" drill="1" shape="square"/>
<pad name="PB5" x="3.81" y="-7.62" drill="1" shape="square"/>
<pad name="AVCC" x="3.81" y="-5.08" drill="1" shape="square"/>
<pad name="AREF" x="3.81" y="-2.54" drill="1" shape="square"/>
<pad name="GND1" x="3.81" y="0" drill="1" shape="square"/>
<pad name="PC0" x="3.81" y="2.54" drill="1" shape="square"/>
<pad name="PC1" x="3.81" y="5.08" drill="1" shape="square"/>
<pad name="PC2" x="3.81" y="7.62" drill="1" shape="square"/>
<pad name="PC3" x="3.81" y="10.16" drill="1" shape="square"/>
<pad name="PC4" x="3.81" y="12.7" drill="1" shape="square"/>
<pad name="PC5" x="3.81" y="15.24" drill="1" shape="square"/>
<wire x1="-5.08" y1="16.51" x2="-5.08" y2="-19.05" width="0.127" layer="21"/>
<wire x1="-5.08" y1="-19.05" x2="5.08" y2="-19.05" width="0.127" layer="21"/>
<wire x1="5.08" y1="-19.05" x2="5.08" y2="16.51" width="0.127" layer="21"/>
<wire x1="5.08" y1="16.51" x2="1.27" y2="16.51" width="0.127" layer="21"/>
<wire x1="1.27" y1="16.51" x2="-1.27" y2="16.51" width="0.127" layer="21"/>
<wire x1="-1.27" y1="16.51" x2="-5.08" y2="16.51" width="0.127" layer="21"/>
<wire x1="-1.27" y1="16.51" x2="-1.27" y2="15.24" width="0.127" layer="21"/>
<wire x1="-1.27" y1="15.24" x2="1.27" y2="15.24" width="0.127" layer="21"/>
<wire x1="1.27" y1="15.24" x2="1.27" y2="16.51" width="0.127" layer="21"/>
<text x="-2.794" y="14.478" size="0.6096" layer="21">PC6</text>
<text x="-2.794" y="12.446" size="0.6096" layer="21">PD0</text>
<text x="-2.794" y="9.906" size="0.6096" layer="21">PD1</text>
<text x="-2.794" y="7.366" size="0.6096" layer="21">PD2</text>
<text x="-2.794" y="4.826" size="0.6096" layer="21">PD3</text>
<text x="-2.794" y="2.286" size="0.6096" layer="21">PD4</text>
<text x="-2.794" y="-0.254" size="0.6096" layer="21">VCC</text>
<text x="-2.794" y="-2.794" size="0.6096" layer="21">GND</text>
<text x="-2.794" y="-5.334" size="0.6096" layer="21">PB6</text>
<text x="-2.794" y="-7.874" size="0.6096" layer="21">PB7</text>
<text x="-2.794" y="-10.414" size="0.6096" layer="21">PD5</text>
<text x="-2.794" y="-12.954" size="0.6096" layer="21">PD6</text>
<text x="-2.794" y="-15.494" size="0.6096" layer="21">PD7</text>
<text x="-2.794" y="-18.034" size="0.6096" layer="21">PB0</text>
<text x="1.27" y="14.478" size="0.6096" layer="21">PC5</text>
<text x="1.27" y="12.446" size="0.6096" layer="21">PC4</text>
<text x="1.27" y="9.906" size="0.6096" layer="21">PC3</text>
<text x="1.27" y="7.366" size="0.6096" layer="21">PC2</text>
<text x="1.27" y="4.826" size="0.6096" layer="21">PC1</text>
<text x="1.27" y="2.286" size="0.6096" layer="21">PC0</text>
<text x="1.016" y="-0.254" size="0.6096" layer="21">GND</text>
<text x="0.508" y="-2.794" size="0.6096" layer="21">AREF</text>
<text x="0.508" y="-5.334" size="0.6096" layer="21">AVCC</text>
<text x="1.27" y="-7.874" size="0.6096" layer="21">PB5</text>
<text x="1.27" y="-10.414" size="0.6096" layer="21">PB4</text>
<text x="1.27" y="-12.954" size="0.6096" layer="21">PB3</text>
<text x="1.27" y="-15.494" size="0.6096" layer="21">PB2</text>
<text x="1.27" y="-18.034" size="0.6096" layer="21">PB1</text>
</package>
<package name="USBASP_PIN">
<pad name="RST" x="-1.27" y="0" drill="0.9" shape="square"/>
<pad name="NC1" x="-1.27" y="2.54" drill="0.9" shape="square"/>
<pad name="MOSI" x="-1.27" y="5.08" drill="0.9" shape="square"/>
<pad name="SCK" x="-1.27" y="-2.54" drill="0.9" shape="square"/>
<pad name="MISO" x="-1.27" y="-5.08" drill="0.9" shape="square"/>
<pad name="GND1" x="1.27" y="-5.08" drill="0.9" shape="square"/>
<pad name="GND" x="1.27" y="-2.54" drill="0.9" shape="square"/>
<pad name="RXD" x="1.27" y="0" drill="0.9" shape="square"/>
<pad name="TXD" x="1.27" y="2.54" drill="0.9" shape="square"/>
<pad name="VCC" x="1.27" y="5.08" drill="0.9" shape="square"/>
<wire x1="-2.54" y1="6.35" x2="-2.54" y2="1.27" width="0.127" layer="21"/>
<wire x1="-2.54" y1="1.27" x2="-2.54" y2="-1.27" width="0.127" layer="21"/>
<wire x1="-2.54" y1="-1.27" x2="-2.54" y2="-6.35" width="0.127" layer="21"/>
<wire x1="-2.54" y1="-6.35" x2="2.54" y2="-6.35" width="0.127" layer="21"/>
<wire x1="2.54" y1="-6.35" x2="2.54" y2="6.35" width="0.127" layer="21"/>
<wire x1="2.54" y1="6.35" x2="-2.54" y2="6.35" width="0.127" layer="21"/>
<wire x1="-2.54" y1="1.27" x2="-3.81" y2="1.27" width="0.127" layer="21"/>
<wire x1="-3.81" y1="1.27" x2="-3.81" y2="-1.27" width="0.127" layer="21"/>
<wire x1="-3.81" y1="-1.27" x2="-2.54" y2="-1.27" width="0.127" layer="21"/>
</package>
<package name="J_SMD">
<smd name="PIN" x="0" y="0" dx="5.08" dy="2.54" layer="1"/>
</package>
</packages>
<symbols>
<symbol name="R">
<pin name="P$1" x="-7.62" y="0" visible="off" length="middle"/>
<pin name="P$2" x="8.89" y="0" visible="off" length="middle" rot="R180"/>
<text x="-6.35" y="2.54" size="1.778" layer="94">&gt;NAME</text>
<text x="-6.35" y="-3.81" size="1.778" layer="94">&gt;VALUE</text>
<wire x1="-2.54" y1="1.27" x2="-2.54" y2="-1.27" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-1.27" x2="3.81" y2="-1.27" width="0.254" layer="94"/>
<wire x1="3.81" y1="-1.27" x2="3.81" y2="1.27" width="0.254" layer="94"/>
<wire x1="3.81" y1="1.27" x2="-2.54" y2="1.27" width="0.254" layer="94"/>
</symbol>
<symbol name="C">
<pin name="PIN_PLUS" x="-7.62" y="0" visible="off" length="middle"/>
<pin name="PIN_GND" x="5.08" y="0" visible="off" length="middle" rot="R180"/>
<wire x1="0" y1="2.54" x2="0" y2="-2.54" width="1.27" layer="94"/>
<wire x1="-2.54" y1="2.54" x2="-2.54" y2="-2.54" width="1.27" layer="94"/>
<text x="-5.08" y="5.08" size="1.778" layer="94">&gt;NAME</text>
<text x="-5.08" y="-7.62" size="1.778" layer="94">&gt;VALUE</text>
<wire x1="-5.715" y1="1.27" x2="-4.445" y2="1.27" width="0.254" layer="94"/>
<wire x1="-5.08" y1="1.905" x2="-5.08" y2="0.635" width="0.254" layer="94"/>
<text x="1.905" y="1.27" size="0.6096" layer="94">GND</text>
</symbol>
<symbol name="BME280">
<pin name="GND" x="-10.16" y="2.54" length="middle" direction="sup"/>
<pin name="SCL" x="-10.16" y="0" length="middle"/>
<pin name="SDA" x="-10.16" y="-2.54" length="middle"/>
<pin name="VCC" x="-10.16" y="5.08" length="middle" direction="sup"/>
<wire x1="-5.08" y1="7.62" x2="-5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-5.08" x2="22.86" y2="-5.08" width="0.254" layer="94"/>
<wire x1="22.86" y1="-5.08" x2="22.86" y2="7.62" width="0.254" layer="94"/>
<wire x1="22.86" y1="7.62" x2="-5.08" y2="7.62" width="0.254" layer="94"/>
<text x="5.08" y="10.16" size="1.778" layer="94">&gt;NAME</text>
<text x="7.62" y="0" size="1.778" layer="94">BME280</text>
</symbol>
<symbol name="GY-SGP30">
<pin name="VIN" x="-7.62" y="2.54" length="middle" direction="pwr"/>
<pin name="GND" x="-7.62" y="0" length="middle" direction="sup"/>
<pin name="SCL" x="-7.62" y="-2.54" length="middle"/>
<pin name="SDA" x="-7.62" y="-5.08" length="middle"/>
<wire x1="-2.54" y1="7.62" x2="-2.54" y2="-10.16" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-10.16" x2="12.7" y2="-10.16" width="0.254" layer="94"/>
<wire x1="12.7" y1="-10.16" x2="12.7" y2="7.62" width="0.254" layer="94"/>
<wire x1="12.7" y1="7.62" x2="-2.54" y2="7.62" width="0.254" layer="94"/>
<text x="-2.54" y="10.16" size="1.778" layer="94">&gt;NAME</text>
</symbol>
<symbol name="C-1">
<pin name="P$1" x="-7.62" y="0" visible="off" length="middle"/>
<pin name="P$2" x="7.62" y="0" visible="off" length="middle" rot="R180"/>
<wire x1="-2.54" y1="0" x2="-0.635" y2="0" width="0.254" layer="94"/>
<wire x1="2.54" y1="0" x2="0.635" y2="0" width="0.254" layer="94"/>
<wire x1="0.635" y1="2.54" x2="0.635" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-0.635" y1="2.54" x2="-0.635" y2="-2.54" width="0.254" layer="94"/>
<text x="-4.445" y="3.175" size="1.778" layer="94">&gt;NAME</text>
<text x="-4.445" y="-5.08" size="1.778" layer="94">&gt;VALUE</text>
</symbol>
<symbol name="RD">
<pin name="P1" x="-7.62" y="0" visible="off" length="middle"/>
<pin name="P2" x="7.62" y="0" visible="off" length="middle" rot="R180"/>
<pin name="P3" x="0" y="7.62" visible="off" length="middle" rot="R270"/>
<wire x1="-2.54" y1="1.27" x2="-2.54" y2="-1.27" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-1.27" x2="2.54" y2="-1.27" width="0.254" layer="94"/>
<wire x1="2.54" y1="-1.27" x2="2.54" y2="1.27" width="0.254" layer="94"/>
<wire x1="2.54" y1="1.27" x2="0" y2="1.27" width="0.254" layer="94"/>
<wire x1="-2.54" y1="1.27" x2="0" y2="1.27" width="0.254" layer="94"/>
<wire x1="0" y1="1.27" x2="0" y2="2.54" width="0.254" layer="94"/>
<polygon width="0.254" layer="94">
<vertex x="-0.635" y="2.54"/>
<vertex x="0" y="1.27"/>
<vertex x="0.635" y="2.54"/>
</polygon>
<text x="-4.445" y="-3.81" size="1.778" layer="94">&gt;NAME</text>
<text x="-5.08" y="-6.35" size="1.778" layer="94">&gt;VALUE</text>
</symbol>
<symbol name="L">
<pin name="P$1" x="-5.08" y="2.54" visible="off" length="middle"/>
<pin name="P$2" x="-5.08" y="-2.54" visible="off" length="middle"/>
<text x="1.905" y="0.635" size="1.778" layer="94">&gt;NAME</text>
<text x="1.905" y="-2.54" size="1.778" layer="94">&gt;VALUE</text>
<wire x1="0" y1="0" x2="0" y2="-1.27" width="0.254" layer="94" curve="-180"/>
<wire x1="0" y1="-1.27" x2="0" y2="-2.54" width="0.254" layer="94" curve="-180"/>
<wire x1="0" y1="1.27" x2="0" y2="0" width="0.254" layer="94" curve="-180"/>
<wire x1="0" y1="2.54" x2="0" y2="1.27" width="0.254" layer="94" curve="-180"/>
</symbol>
<symbol name="MICROPHONE">
<circle x="0" y="0" radius="5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="5.08" x2="5.08" y2="-5.08" width="0.254" layer="94"/>
<pin name="P$1" x="-10.16" y="2.54" visible="off" length="middle"/>
<pin name="P$2" x="-10.16" y="-2.54" visible="off" length="middle"/>
<wire x1="-5.08" y1="2.54" x2="-4.445" y2="2.54" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-2.54" x2="-4.445" y2="-2.54" width="0.254" layer="94"/>
<text x="7.62" y="2.54" size="1.778" layer="94">&gt;NAME</text>
<text x="7.62" y="-2.54" size="1.778" layer="94">&gt;VALUE</text>
</symbol>
<symbol name="LM358">
<pin name="A_OUT" x="-10.16" y="2.54" visible="off" length="middle" direction="out"/>
<pin name="A-" x="-10.16" y="0" visible="off" length="middle" direction="in"/>
<pin name="A+" x="-10.16" y="-2.54" visible="off" length="middle" direction="in"/>
<pin name="VEE" x="-10.16" y="-5.08" visible="off" length="middle" direction="pwr"/>
<pin name="VCC" x="10.16" y="2.54" visible="off" length="middle" direction="pwr" rot="R180"/>
<pin name="B_OUT" x="10.16" y="0" visible="off" length="middle" direction="out" rot="R180"/>
<pin name="B-" x="10.16" y="-2.54" visible="off" length="middle" direction="in" rot="R180"/>
<pin name="B+" x="10.16" y="-5.08" visible="off" length="middle" direction="in" rot="R180"/>
<wire x1="-5.08" y1="5.08" x2="-5.08" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-7.62" x2="5.08" y2="-7.62" width="0.254" layer="94"/>
<wire x1="5.08" y1="-7.62" x2="5.08" y2="5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="5.08" x2="0.635" y2="5.08" width="0.254" layer="94"/>
<wire x1="0.635" y1="5.08" x2="-0.635" y2="5.08" width="0.254" layer="94"/>
<wire x1="-0.635" y1="5.08" x2="-5.08" y2="5.08" width="0.254" layer="94"/>
<wire x1="-0.635" y1="5.08" x2="-0.635" y2="4.445" width="0.254" layer="94"/>
<wire x1="-0.635" y1="4.445" x2="0.635" y2="4.445" width="0.254" layer="94"/>
<wire x1="0.635" y1="4.445" x2="0.635" y2="5.08" width="0.254" layer="94"/>
<text x="-4.445" y="2.54" size="0.6096" layer="94">A_OUT</text>
<text x="-4.445" y="0" size="0.6096" layer="94">A-</text>
<text x="-4.445" y="-2.54" size="0.6096" layer="94">A+</text>
<text x="-4.445" y="-5.08" size="0.6096" layer="94">Vee</text>
<text x="3.175" y="2.54" size="0.6096" layer="94">Vcc</text>
<text x="1.905" y="0" size="0.6096" layer="94">B_OUT</text>
<text x="3.81" y="-2.54" size="0.6096" layer="94">B-</text>
<text x="3.81" y="-5.08" size="0.6096" layer="94">B+</text>
<text x="-3.81" y="5.715" size="1.4224" layer="94">&gt;NAME</text>
<text x="-3.81" y="-9.525" size="1.4224" layer="94">&gt;VALUE</text>
</symbol>
<symbol name="VOLTAGE_REGULATOR">
<pin name="IN" x="-10.16" y="2.54" visible="off" length="middle" direction="pwr"/>
<pin name="GND" x="0" y="-7.62" visible="off" length="middle" direction="pwr" rot="R90"/>
<pin name="OUT" x="10.16" y="2.54" visible="off" length="middle" direction="sup" rot="R180"/>
<wire x1="-5.08" y1="5.08" x2="-5.08" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-2.54" x2="5.08" y2="-2.54" width="0.254" layer="94"/>
<wire x1="5.08" y1="-2.54" x2="5.08" y2="5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="5.08" x2="-5.08" y2="5.08" width="0.254" layer="94"/>
<text x="-2.54" y="10.16" size="1.778" layer="94">&gt;NAME</text>
<text x="-2.54" y="7.62" size="1.778" layer="94">&gt;VALUE</text>
<text x="-3.81" y="2.54" size="1.778" layer="94">in</text>
<text x="-2.54" y="-1.27" size="1.778" layer="94">GND</text>
<text x="1.27" y="2.54" size="1.778" layer="94">out</text>
</symbol>
<symbol name="ATMEGA328P">
<pin name="GND" x="-20.32" y="0" visible="off" length="middle" direction="pwr"/>
<pin name="VCC" x="-20.32" y="2.54" visible="off" length="middle" direction="pwr"/>
<pin name="PB6" x="-20.32" y="-2.54" visible="off" length="middle"/>
<pin name="PD4" x="-20.32" y="5.08" visible="off" length="middle"/>
<pin name="PB7" x="-20.32" y="-5.08" visible="off" length="middle"/>
<pin name="PD3" x="-20.32" y="7.62" visible="off" length="middle"/>
<pin name="PD5" x="-20.32" y="-7.62" visible="off" length="middle"/>
<pin name="PD2" x="-20.32" y="10.16" visible="off" length="middle"/>
<pin name="PD6" x="-20.32" y="-10.16" visible="off" length="middle"/>
<pin name="PD1" x="-20.32" y="12.7" visible="off" length="middle"/>
<pin name="PD7" x="-20.32" y="-12.7" visible="off" length="middle"/>
<pin name="PD0" x="-20.32" y="15.24" visible="off" length="middle"/>
<pin name="PB0" x="-20.32" y="-15.24" visible="off" length="middle"/>
<pin name="PC6" x="-20.32" y="17.78" visible="off" length="middle"/>
<pin name="PC5" x="20.32" y="17.78" visible="off" length="middle" rot="R180"/>
<pin name="PC4" x="20.32" y="15.24" visible="off" length="middle" rot="R180"/>
<pin name="PC3" x="20.32" y="12.7" visible="off" length="middle" rot="R180"/>
<pin name="PC2" x="20.32" y="10.16" visible="off" length="middle" rot="R180"/>
<pin name="PC1" x="20.32" y="7.62" visible="off" length="middle" rot="R180"/>
<pin name="PC0" x="20.32" y="5.08" visible="off" length="middle" rot="R180"/>
<pin name="GND1" x="20.32" y="2.54" visible="off" length="middle" direction="pwr" rot="R180"/>
<pin name="AREF" x="20.32" y="0" visible="off" length="middle" rot="R180"/>
<pin name="AVCC" x="20.32" y="-2.54" visible="off" length="middle" direction="pwr" rot="R180"/>
<pin name="PB5" x="20.32" y="-5.08" visible="off" length="middle" rot="R180"/>
<pin name="PB4" x="20.32" y="-7.62" visible="off" length="middle" rot="R180"/>
<pin name="PB3" x="20.32" y="-10.16" visible="off" length="middle" rot="R180"/>
<pin name="PB2" x="20.32" y="-12.7" visible="off" length="middle" rot="R180"/>
<pin name="PB1" x="20.32" y="-15.24" visible="off" length="middle" rot="R180"/>
<text x="-15.24" y="17.78" size="0.8128" layer="94">(PCINT14/RESET) PC6</text>
<text x="-15.24" y="15.24" size="0.8128" layer="94">(PCINT16/RXD) PD0</text>
<text x="-15.24" y="12.7" size="0.8128" layer="94">(PCINT17/TXD) PD1</text>
<text x="-15.24" y="10.16" size="0.8128" layer="94">(PCINT18/INT0) PD2</text>
<text x="-15.24" y="7.62" size="0.8128" layer="94">(PCINT19/OC2B/INT1) PD3</text>
<text x="-15.24" y="5.08" size="0.8128" layer="94">(PCINT20/XCK/T0) PD4</text>
<text x="-12.7" y="2.54" size="0.8128" layer="94">VCC</text>
<text x="-12.7" y="0" size="0.8128" layer="94">GND</text>
<text x="-15.24" y="-2.54" size="0.8128" layer="94">(PCINT6/XTAL1/TOSC1) PB6</text>
<text x="-15.24" y="-5.08" size="0.8128" layer="94">(PCINT7/XTAL2/TOSC2) PB7</text>
<text x="-15.24" y="-7.62" size="0.8128" layer="94">(PCINT21/OC0B/T1) PD5</text>
<text x="-15.24" y="-10.16" size="0.8128" layer="94">(PCINT22/OC0A/AIN0) PD6</text>
<text x="-15.24" y="-12.7" size="0.8128" layer="94">(PCINT23/AIN1) PD7</text>
<text x="-15.24" y="-15.24" size="0.8128" layer="94">(PCINT0/CLKO/ICP1) PB0</text>
<text x="0" y="17.78" size="0.8128" layer="94">PC5 (ADC5/SCL/PCINT13)</text>
<text x="0" y="15.24" size="0.8128" layer="94">PC4 (ADC4/SDA/PCINT12)</text>
<text x="2.54" y="12.7" size="0.8128" layer="94">PC3 (ADC3/PCINT11)</text>
<text x="2.54" y="10.16" size="0.8128" layer="94">PC2 (ADC2/PCINT10)</text>
<text x="2.54" y="7.62" size="0.8128" layer="94">PC1 (ADC1/PCINT9)</text>
<text x="2.54" y="5.08" size="0.8128" layer="94">PC0 (ADC0/PCINT8)</text>
<text x="7.62" y="2.54" size="0.8128" layer="94">GND</text>
<text x="7.62" y="0" size="0.8128" layer="94">AREF</text>
<text x="7.62" y="-2.54" size="0.8128" layer="94">AVCC</text>
<text x="2.54" y="-5.08" size="0.8128" layer="94">PB5 (SCK/PCINT5)</text>
<text x="2.54" y="-7.62" size="0.8128" layer="94">PB4 (MISO/PCINT4)</text>
<text x="0" y="-10.16" size="0.8128" layer="94">PB3 (MOSI/OC2A/PCINT3)</text>
<text x="0" y="-12.7" size="0.8128" layer="94">PB2 (SS/OC1B/PCINT2)</text>
<text x="2.54" y="-15.24" size="0.8128" layer="94">PB1 (OC1A/PCINT1)</text>
<wire x1="-15.24" y1="22.86" x2="-15.24" y2="-20.32" width="0.254" layer="94"/>
<wire x1="-15.24" y1="-20.32" x2="15.24" y2="-20.32" width="0.254" layer="94"/>
<wire x1="15.24" y1="-20.32" x2="15.24" y2="22.86" width="0.254" layer="94"/>
<wire x1="15.24" y1="22.86" x2="2.54" y2="22.86" width="0.254" layer="94"/>
<wire x1="2.54" y1="22.86" x2="-2.54" y2="22.86" width="0.254" layer="94"/>
<wire x1="-2.54" y1="22.86" x2="-15.24" y2="22.86" width="0.254" layer="94"/>
<wire x1="-2.54" y1="22.86" x2="-2.54" y2="20.32" width="0.254" layer="94"/>
<wire x1="-2.54" y1="20.32" x2="2.54" y2="20.32" width="0.254" layer="94"/>
<wire x1="2.54" y1="20.32" x2="2.54" y2="22.86" width="0.254" layer="94"/>
<text x="-5.08" y="25.4" size="1.778" layer="94">&gt;NAME</text>
<text x="-5.08" y="-25.4" size="1.778" layer="94">&gt;VALUE</text>
</symbol>
<symbol name="USBASP_PIN">
<pin name="MOSI" x="-10.16" y="5.08" visible="off" length="middle"/>
<pin name="NC1" x="-10.16" y="2.54" visible="off" length="middle" direction="nc"/>
<pin name="RESET" x="-10.16" y="0" visible="off" length="middle"/>
<pin name="SCK" x="-10.16" y="-2.54" visible="off" length="middle"/>
<pin name="MISO" x="-10.16" y="-5.08" visible="off" length="middle"/>
<pin name="VCC" x="10.16" y="5.08" visible="off" length="middle" direction="pwr" rot="R180"/>
<pin name="TXD" x="10.16" y="2.54" visible="off" length="middle" rot="R180"/>
<pin name="RXD" x="10.16" y="0" visible="off" length="middle" rot="R180"/>
<pin name="GND" x="10.16" y="-2.54" visible="off" length="middle" direction="pwr" rot="R180"/>
<pin name="GND1" x="10.16" y="-5.08" visible="off" length="middle" direction="pwr" rot="R180"/>
<wire x1="-5.08" y1="7.62" x2="-5.08" y2="1.27" width="0.254" layer="94"/>
<wire x1="-5.08" y1="1.27" x2="-5.08" y2="-1.27" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-1.27" x2="-5.08" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-7.62" x2="5.08" y2="-7.62" width="0.254" layer="94"/>
<wire x1="5.08" y1="-7.62" x2="5.08" y2="7.62" width="0.254" layer="94"/>
<wire x1="5.08" y1="7.62" x2="-5.08" y2="7.62" width="0.254" layer="94"/>
<wire x1="-5.08" y1="1.27" x2="-3.81" y2="1.27" width="0.254" layer="94"/>
<wire x1="-3.81" y1="1.27" x2="-3.81" y2="-1.27" width="0.254" layer="94"/>
<wire x1="-3.81" y1="-1.27" x2="-5.08" y2="-1.27" width="0.254" layer="94"/>
<text x="-3.81" y="5.08" size="0.8128" layer="94">MOSI</text>
<text x="-3.175" y="0" size="0.8128" layer="94">RST</text>
<text x="-3.81" y="-2.54" size="0.8128" layer="94">SCK</text>
<text x="-3.81" y="-5.08" size="0.8128" layer="94">MISO</text>
<text x="1.905" y="5.08" size="0.8128" layer="94">VCC</text>
<text x="1.905" y="-2.54" size="0.8128" layer="94">GND</text>
<text x="1.905" y="-5.08" size="0.8128" layer="94">GND</text>
<text x="-1.905" y="8.255" size="0.8128" layer="94">&gt;NAME</text>
<text x="-1.905" y="-9.525" size="0.8128" layer="94">&gt;VALUE</text>
<text x="1.905" y="0" size="0.8128" layer="94">RXD</text>
<text x="1.905" y="2.54" size="0.8128" layer="94">TXD</text>
</symbol>
<symbol name="J_SMD">
<pin name="PIN" x="-7.62" y="0" visible="off" length="middle"/>
<wire x1="-2.54" y1="2.54" x2="-2.54" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-2.54" x2="2.54" y2="-2.54" width="0.254" layer="94"/>
<wire x1="2.54" y1="-2.54" x2="2.54" y2="2.54" width="0.254" layer="94"/>
<wire x1="2.54" y1="2.54" x2="-2.54" y2="2.54" width="0.254" layer="94"/>
<text x="5.08" y="0" size="1.778" layer="94">&gt;NAME</text>
<text x="5.08" y="-2.54" size="1.778" layer="94">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="R" prefix="R">
<gates>
<gate name="G$1" symbol="R" x="0" y="0"/>
</gates>
<devices>
<device name="" package="R">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
<connect gate="G$1" pin="P$2" pad="P$2"/>
</connects>
<technologies>
<technology name="">
<attribute name="R" value="" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="C" prefix="C">
<gates>
<gate name="G$1" symbol="C" x="2.54" y="0"/>
</gates>
<devices>
<device name="" package="C">
<connects>
<connect gate="G$1" pin="PIN_GND" pad="PIN_GND"/>
<connect gate="G$1" pin="PIN_PLUS" pad="PIN_PLUS"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="BME280" prefix="U">
<gates>
<gate name="G$1" symbol="BME280" x="0" y="0"/>
</gates>
<devices>
<device name="" package="BME280">
<connects>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="SCL" pad="SCL"/>
<connect gate="G$1" pin="SDA" pad="SDA"/>
<connect gate="G$1" pin="VCC" pad="VCC"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="GY-SGP30" prefix="U">
<gates>
<gate name="G$1" symbol="GY-SGP30" x="-5.08" y="0"/>
</gates>
<devices>
<device name="" package="GY-SGP30">
<connects>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="SCL" pad="SCL"/>
<connect gate="G$1" pin="SDA" pad="SDA"/>
<connect gate="G$1" pin="VIN" pad="VIN"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="C-1" prefix="C">
<gates>
<gate name="G$1" symbol="C-1" x="0" y="0"/>
</gates>
<devices>
<device name="" package="C-1">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
<connect gate="G$1" pin="P$2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="RD" prefix="R">
<gates>
<gate name="G$1" symbol="RD" x="0" y="0"/>
</gates>
<devices>
<device name="" package="RD-3362H">
<connects>
<connect gate="G$1" pin="P1" pad="P1"/>
<connect gate="G$1" pin="P2" pad="P2"/>
<connect gate="G$1" pin="P3" pad="P3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="3296-Z" package="RD-3296Z">
<connects>
<connect gate="G$1" pin="P1" pad="P1"/>
<connect gate="G$1" pin="P2" pad="P2"/>
<connect gate="G$1" pin="P3" pad="P3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="L" prefix="L">
<gates>
<gate name="G$1" symbol="L" x="0" y="0"/>
</gates>
<devices>
<device name="" package="L-RLB0914">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
<connect gate="G$1" pin="P$2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="L-EC24" package="L-EC24">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
<connect gate="G$1" pin="P$2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MICROPHONE" prefix="BM">
<gates>
<gate name="G$1" symbol="MICROPHONE" x="0" y="0"/>
</gates>
<devices>
<device name="" package="MICROPHONE">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
<connect gate="G$1" pin="P$2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="LM358" prefix="U">
<gates>
<gate name="G$1" symbol="LM358" x="0" y="0"/>
</gates>
<devices>
<device name="" package="DIP8">
<connects>
<connect gate="G$1" pin="A+" pad="PIN_3"/>
<connect gate="G$1" pin="A-" pad="PIN_2"/>
<connect gate="G$1" pin="A_OUT" pad="PIN_1"/>
<connect gate="G$1" pin="B+" pad="PIN_5"/>
<connect gate="G$1" pin="B-" pad="PIN_6"/>
<connect gate="G$1" pin="B_OUT" pad="PIN_7"/>
<connect gate="G$1" pin="VCC" pad="PIN_8"/>
<connect gate="G$1" pin="VEE" pad="PIN_4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="VOLTAGE_REGULATOR" prefix="U">
<gates>
<gate name="G$1" symbol="VOLTAGE_REGULATOR" x="0" y="0"/>
</gates>
<devices>
<device name="" package="VOLTAGE_REGULATOR">
<connects>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="IN" pad="IN"/>
<connect gate="G$1" pin="OUT" pad="OUT"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="ATMEGA328P" prefix="U">
<gates>
<gate name="G$1" symbol="ATMEGA328P" x="0" y="0"/>
</gates>
<devices>
<device name="" package="ATMEGA328P">
<connects>
<connect gate="G$1" pin="AREF" pad="AREF"/>
<connect gate="G$1" pin="AVCC" pad="AVCC"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="GND1" pad="GND1"/>
<connect gate="G$1" pin="PB0" pad="PB0"/>
<connect gate="G$1" pin="PB1" pad="PB1"/>
<connect gate="G$1" pin="PB2" pad="PB2"/>
<connect gate="G$1" pin="PB3" pad="PB3"/>
<connect gate="G$1" pin="PB4" pad="PB4"/>
<connect gate="G$1" pin="PB5" pad="PB5"/>
<connect gate="G$1" pin="PB6" pad="PB6"/>
<connect gate="G$1" pin="PB7" pad="PB7"/>
<connect gate="G$1" pin="PC0" pad="PC0"/>
<connect gate="G$1" pin="PC1" pad="PC1"/>
<connect gate="G$1" pin="PC2" pad="PC2"/>
<connect gate="G$1" pin="PC3" pad="PC3"/>
<connect gate="G$1" pin="PC4" pad="PC4"/>
<connect gate="G$1" pin="PC5" pad="PC5"/>
<connect gate="G$1" pin="PC6" pad="PC6"/>
<connect gate="G$1" pin="PD0" pad="PD0"/>
<connect gate="G$1" pin="PD1" pad="PD1"/>
<connect gate="G$1" pin="PD2" pad="PD2"/>
<connect gate="G$1" pin="PD3" pad="PD3"/>
<connect gate="G$1" pin="PD4" pad="PD4"/>
<connect gate="G$1" pin="PD5" pad="PD5"/>
<connect gate="G$1" pin="PD6" pad="PD6"/>
<connect gate="G$1" pin="PD7" pad="PD7"/>
<connect gate="G$1" pin="VCC" pad="VCC"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="USBASP_PIN" prefix="J">
<gates>
<gate name="G$1" symbol="USBASP_PIN" x="0" y="0"/>
</gates>
<devices>
<device name="" package="USBASP_PIN">
<connects>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="GND1" pad="GND1"/>
<connect gate="G$1" pin="MISO" pad="MISO"/>
<connect gate="G$1" pin="MOSI" pad="MOSI"/>
<connect gate="G$1" pin="NC1" pad="NC1"/>
<connect gate="G$1" pin="RESET" pad="RST"/>
<connect gate="G$1" pin="RXD" pad="RXD"/>
<connect gate="G$1" pin="SCK" pad="SCK"/>
<connect gate="G$1" pin="TXD" pad="TXD"/>
<connect gate="G$1" pin="VCC" pad="VCC"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="J_SMD" prefix="J">
<gates>
<gate name="G$1" symbol="J_SMD" x="-2.54" y="0"/>
</gates>
<devices>
<device name="" package="J_SMD">
<connects>
<connect gate="G$1" pin="PIN" pad="PIN"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<groups>
<schematic_group name="BME_280_TEMP_HUM1"/>
<schematic_group name="GY-SGP1"/>
<schematic_group name="ATMEGA1"/>
<schematic_group name="NOISE1"/>
<schematic_group name="INPUT_CONNECTOR"/>
</groups>
<parts>
<part name="R21" library="my_devices" deviceset="R" device="" value="10K"/>
<part name="U5" library="my_devices" deviceset="BME280" device="" value="BMP280 5V module"/>
<part name="U9" library="my_devices" deviceset="GY-SGP30" device=""/>
<part name="C6" library="my_devices" deviceset="C" device="" value="1000 uF"/>
<part name="U7" library="my_devices" deviceset="LM358" device=""/>
<part name="BM1" library="my_devices" deviceset="MICROPHONE" device="" value="EM6050P"/>
<part name="R18" library="my_devices" deviceset="R" device="" value="3K"/>
<part name="C8" library="my_devices" deviceset="C-1" device="" value="0.1 uF"/>
<part name="R20" library="my_devices" deviceset="RD" device="3296-Z" value="200K"/>
<part name="R23" library="my_devices" deviceset="RD" device="3296-Z" value="200K"/>
<part name="U6" library="my_devices" deviceset="VOLTAGE_REGULATOR" device="" value="LM317L"/>
<part name="L3" library="my_devices" deviceset="L" device="L-EC24" value="EC24-561K, 560 uH"/>
<part name="C10" library="my_devices" deviceset="C" device="" value="10 uF"/>
<part name="R19" library="my_devices" deviceset="R" device="" value="200K"/>
<part name="R17" library="my_devices" deviceset="RD" device="" value="10K"/>
<part name="C11" library="my_devices" deviceset="C-1" device="" value="0.1 uF"/>
<part name="R22" library="my_devices" deviceset="R" device="" value="200K"/>
<part name="L2" library="my_devices" deviceset="L" device="L-EC24" value="EC24-561K, 560 uH"/>
<part name="C7" library="my_devices" deviceset="C" device="" value="10 uF"/>
<part name="U8" library="my_devices" deviceset="ATMEGA328P" device=""/>
<part name="C9" library="my_devices" deviceset="C-1" device="" value="0.1 uF"/>
<part name="J10" library="my_devices" deviceset="USBASP_PIN" device=""/>
<part name="J1" library="my_devices" deviceset="J_SMD" device=""/>
<part name="J2" library="my_devices" deviceset="J_SMD" device=""/>
<part name="J3" library="my_devices" deviceset="J_SMD" device=""/>
</parts>
<sheets>
<sheet>
<plain>
<text x="-243.84" y="335.28" size="1.778" layer="91" grouprefs="BME_280_TEMP_HUM1">5V Module required!</text>
<text x="-187.96" y="93.98" size="1.778" layer="91" grouprefs="NOISE1">Initial voltage in OUTDOOR_MIDDLEPOINT is 2.5V
You needs to ajust it using osciloscope by measuring NOISE_LEVEL signal.
In my case I setup ~1.8V in OUTDOOR_MIDDLEPOINT</text>
</plain>
<instances>
<instance part="R21" gate="G$1" x="-175.26" y="284.48" smashed="yes" rot="R90" grouprefs="ATMEGA1">
<attribute name="NAME" x="-177.8" y="278.13" size="1.778" layer="94" rot="R90"/>
<attribute name="VALUE" x="-171.45" y="278.13" size="1.778" layer="94" rot="R90"/>
</instance>
<instance part="U5" gate="G$1" x="-243.84" y="342.9" smashed="yes" grouprefs="BME_280_TEMP_HUM1">
<attribute name="NAME" x="-238.76" y="353.06" size="1.778" layer="94"/>
</instance>
<instance part="U9" gate="G$1" x="-142.24" y="345.44" smashed="yes" grouprefs="GY-SGP1">
<attribute name="NAME" x="-144.78" y="355.6" size="1.778" layer="94"/>
</instance>
<instance part="C6" gate="G$1" x="-271.78" y="256.54" smashed="yes" rot="R270" grouprefs="INPUT_CONNECTOR">
<attribute name="NAME" x="-266.7" y="261.62" size="1.778" layer="94" rot="R270"/>
<attribute name="VALUE" x="-279.4" y="261.62" size="1.778" layer="94" rot="R270"/>
</instance>
<instance part="U7" gate="G$1" x="-172.72" y="25.4" smashed="yes" grouprefs="NOISE1">
<attribute name="NAME" x="-176.53" y="31.115" size="1.4224" layer="94"/>
<attribute name="VALUE" x="-176.53" y="15.875" size="1.4224" layer="94"/>
</instance>
<instance part="BM1" gate="G$1" x="-223.52" y="20.32" smashed="yes" rot="R180" grouprefs="NOISE1">
<attribute name="NAME" x="-231.14" y="17.78" size="1.778" layer="94" rot="R180"/>
<attribute name="VALUE" x="-231.14" y="22.86" size="1.778" layer="94" rot="R180"/>
</instance>
<instance part="R18" gate="G$1" x="-208.28" y="33.02" smashed="yes" rot="R270" grouprefs="NOISE1">
<attribute name="NAME" x="-205.74" y="39.37" size="1.778" layer="94" rot="R270"/>
<attribute name="VALUE" x="-212.09" y="39.37" size="1.778" layer="94" rot="R270"/>
</instance>
<instance part="C8" gate="G$1" x="-198.12" y="22.86" smashed="yes" grouprefs="NOISE1">
<attribute name="NAME" x="-202.565" y="26.035" size="1.778" layer="94"/>
<attribute name="VALUE" x="-202.565" y="17.78" size="1.778" layer="94"/>
</instance>
<instance part="R20" gate="G$1" x="-182.88" y="53.34" smashed="yes" rot="R90" grouprefs="NOISE1">
<attribute name="NAME" x="-179.07" y="48.895" size="1.778" layer="94" rot="R90"/>
<attribute name="VALUE" x="-176.53" y="48.26" size="1.778" layer="94" rot="R90"/>
</instance>
<instance part="R23" gate="G$1" x="-147.32" y="22.86" smashed="yes" rot="R90" grouprefs="NOISE1">
<attribute name="NAME" x="-143.51" y="18.415" size="1.778" layer="94" rot="R90"/>
<attribute name="VALUE" x="-140.97" y="17.78" size="1.778" layer="94" rot="R90"/>
</instance>
<instance part="U6" gate="G$1" x="-223.52" y="88.9" smashed="yes" grouprefs="NOISE1">
<attribute name="NAME" x="-226.06" y="99.06" size="1.778" layer="94"/>
<attribute name="VALUE" x="-226.06" y="96.52" size="1.778" layer="94"/>
</instance>
<instance part="L3" gate="G$1" x="-195.58" y="96.52" smashed="yes" rot="R90" grouprefs="NOISE1">
<attribute name="NAME" x="-196.215" y="98.425" size="1.778" layer="94" rot="R90"/>
<attribute name="VALUE" x="-193.04" y="98.425" size="1.778" layer="94" rot="R90"/>
</instance>
<instance part="C10" gate="G$1" x="-177.8" y="83.82" smashed="yes" rot="R270" grouprefs="NOISE1">
<attribute name="NAME" x="-172.72" y="88.9" size="1.778" layer="94" rot="R270"/>
<attribute name="VALUE" x="-185.42" y="88.9" size="1.778" layer="94" rot="R270"/>
</instance>
<instance part="R19" gate="G$1" x="-190.5" y="10.16" smashed="yes" rot="R90" grouprefs="NOISE1">
<attribute name="NAME" x="-193.04" y="3.81" size="1.778" layer="94" rot="R90"/>
<attribute name="VALUE" x="-186.69" y="3.81" size="1.778" layer="94" rot="R90"/>
</instance>
<instance part="R17" gate="G$1" x="-210.82" y="81.28" smashed="yes" rot="R90" grouprefs="NOISE1">
<attribute name="NAME" x="-207.01" y="76.835" size="1.778" layer="94" rot="R90"/>
<attribute name="VALUE" x="-204.47" y="76.2" size="1.778" layer="94" rot="R90"/>
</instance>
<instance part="C11" gate="G$1" x="-170.18" y="43.18" smashed="yes" grouprefs="NOISE1">
<attribute name="NAME" x="-174.625" y="46.355" size="1.778" layer="94"/>
<attribute name="VALUE" x="-174.625" y="38.1" size="1.778" layer="94"/>
</instance>
<instance part="R22" gate="G$1" x="-157.48" y="50.8" smashed="yes" rot="R90" grouprefs="NOISE1">
<attribute name="NAME" x="-160.02" y="44.45" size="1.778" layer="94" rot="R90"/>
<attribute name="VALUE" x="-153.67" y="44.45" size="1.778" layer="94" rot="R90"/>
</instance>
<instance part="L2" gate="G$1" x="-220.98" y="139.7" smashed="yes" rot="R90" grouprefs="NOISE1">
<attribute name="NAME" x="-221.615" y="141.605" size="1.778" layer="94" rot="R90"/>
<attribute name="VALUE" x="-218.44" y="141.605" size="1.778" layer="94" rot="R90"/>
</instance>
<instance part="C7" gate="G$1" x="-210.82" y="127" smashed="yes" rot="R270" grouprefs="NOISE1">
<attribute name="NAME" x="-205.74" y="132.08" size="1.778" layer="94" rot="R270"/>
<attribute name="VALUE" x="-218.44" y="132.08" size="1.778" layer="94" rot="R270"/>
</instance>
<instance part="U8" gate="G$1" x="-154.94" y="241.3" smashed="yes" grouprefs="ATMEGA1">
<attribute name="NAME" x="-160.02" y="266.7" size="1.778" layer="94"/>
<attribute name="VALUE" x="-160.02" y="215.9" size="1.778" layer="94"/>
</instance>
<instance part="C9" gate="G$1" x="-187.96" y="276.86" smashed="yes" grouprefs="ATMEGA1">
<attribute name="NAME" x="-192.405" y="280.035" size="1.778" layer="94"/>
<attribute name="VALUE" x="-192.405" y="271.78" size="1.778" layer="94"/>
</instance>
<instance part="J10" gate="G$1" x="-101.6" y="218.44" smashed="yes" grouprefs="ATMEGA1">
<attribute name="NAME" x="-103.505" y="226.695" size="0.8128" layer="94"/>
<attribute name="VALUE" x="-103.505" y="208.915" size="0.8128" layer="94"/>
</instance>
<instance part="J1" gate="G$1" x="-297.18" y="264.16" smashed="yes" rot="R180" grouprefs="INPUT_CONNECTOR">
<attribute name="NAME" x="-302.26" y="264.16" size="1.778" layer="94" rot="R180"/>
<attribute name="VALUE" x="-302.26" y="266.7" size="1.778" layer="94" rot="R180"/>
</instance>
<instance part="J2" gate="G$1" x="-297.18" y="251.46" smashed="yes" rot="R180" grouprefs="INPUT_CONNECTOR">
<attribute name="NAME" x="-302.26" y="251.46" size="1.778" layer="94" rot="R180"/>
<attribute name="VALUE" x="-302.26" y="254" size="1.778" layer="94" rot="R180"/>
</instance>
<instance part="J3" gate="G$1" x="-297.18" y="238.76" smashed="yes" rot="R180" grouprefs="INPUT_CONNECTOR">
<attribute name="NAME" x="-302.26" y="238.76" size="1.778" layer="94" rot="R180"/>
<attribute name="VALUE" x="-302.26" y="241.3" size="1.778" layer="94" rot="R180"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="OUTDOOR_+5V" class="0">
<segment>
<wire x1="-149.86" y1="347.98" x2="-170.18" y2="347.98" width="0.1524" layer="91" grouprefs="GY-SGP1"/>
<label x="-170.18" y="347.98" size="1.778" layer="95" grouprefs="GY-SGP1"/>
<pinref part="U9" gate="G$1" pin="VIN"/>
</segment>
<segment>
<wire x1="-254" y1="347.98" x2="-269.24" y2="347.98" width="0.1524" layer="91" grouprefs="BME_280_TEMP_HUM1"/>
<wire x1="-269.24" y1="347.98" x2="-269.24" y2="358.14" width="0.1524" layer="91" grouprefs="BME_280_TEMP_HUM1"/>
<label x="-271.78" y="358.14" size="1.778" layer="95" grouprefs="BME_280_TEMP_HUM1"/>
<pinref part="U5" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="C6" gate="G$1" pin="PIN_PLUS"/>
<wire x1="-289.56" y1="264.16" x2="-271.78" y2="264.16" width="0.1524" layer="91" grouprefs="INPUT_CONNECTOR"/>
<wire x1="-271.78" y1="264.16" x2="-261.62" y2="264.16" width="0.1524" layer="91" grouprefs="INPUT_CONNECTOR"/>
<junction x="-271.78" y="264.16" grouprefs="INPUT_CONNECTOR"/>
<label x="-276.86" y="266.7" size="1.778" layer="95" grouprefs="INPUT_CONNECTOR"/>
<pinref part="J1" gate="G$1" pin="PIN"/>
</segment>
<segment>
<pinref part="L2" gate="G$1" pin="P$1"/>
<wire x1="-248.92" y1="134.62" x2="-223.52" y2="134.62" width="0.1524" layer="91" grouprefs="NOISE1"/>
<label x="-251.46" y="134.62" size="1.778" layer="95" grouprefs="NOISE1"/>
</segment>
<segment>
<pinref part="U8" gate="G$1" pin="AREF"/>
<wire x1="-134.62" y1="241.3" x2="-116.84" y2="241.3" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<label x="-129.54" y="241.3" size="1.778" layer="95" grouprefs="ATMEGA1"/>
<pinref part="U8" gate="G$1" pin="AVCC"/>
<wire x1="-134.62" y1="238.76" x2="-134.62" y2="241.3" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<junction x="-134.62" y="241.3" grouprefs="ATMEGA1"/>
</segment>
<segment>
<pinref part="U8" gate="G$1" pin="VCC"/>
<wire x1="-175.26" y1="243.84" x2="-198.12" y2="243.84" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<label x="-200.66" y="243.84" size="1.778" layer="95" grouprefs="ATMEGA1"/>
</segment>
<segment>
<pinref part="R21" gate="G$1" pin="P$2"/>
<wire x1="-175.26" y1="293.37" x2="-210.82" y2="293.37" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<label x="-208.28" y="294.64" size="1.778" layer="95" grouprefs="ATMEGA1"/>
</segment>
<segment>
<pinref part="J10" gate="G$1" pin="VCC"/>
<wire x1="-91.44" y1="223.52" x2="-71.12" y2="223.52" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<label x="-88.9" y="223.52" size="1.778" layer="95" grouprefs="ATMEGA1"/>
</segment>
</net>
<net name="OUTDOOR_GND" class="0">
<segment>
<wire x1="-294.64" y1="345.44" x2="-254" y2="345.44" width="0.1524" layer="91" grouprefs="BME_280_TEMP_HUM1"/>
<pinref part="U5" gate="G$1" pin="GND"/>
<label x="-294.64" y="345.44" size="1.778" layer="95" grouprefs="BME_280_TEMP_HUM1"/>
</segment>
<segment>
<wire x1="-149.86" y1="345.44" x2="-170.18" y2="345.44" width="0.1524" layer="91" grouprefs="GY-SGP1"/>
<pinref part="U9" gate="G$1" pin="GND"/>
<label x="-170.18" y="345.44" size="1.778" layer="95" grouprefs="GY-SGP1"/>
</segment>
<segment>
<pinref part="C6" gate="G$1" pin="PIN_GND"/>
<wire x1="-289.56" y1="251.46" x2="-271.78" y2="251.46" width="0.1524" layer="91" grouprefs="INPUT_CONNECTOR"/>
<wire x1="-271.78" y1="251.46" x2="-261.62" y2="251.46" width="0.1524" layer="91" grouprefs="INPUT_CONNECTOR"/>
<junction x="-271.78" y="251.46" grouprefs="INPUT_CONNECTOR"/>
<label x="-276.86" y="248.92" size="1.778" layer="95" grouprefs="INPUT_CONNECTOR"/>
<pinref part="J2" gate="G$1" pin="PIN"/>
</segment>
<segment>
<pinref part="BM1" gate="G$1" pin="P$1"/>
<wire x1="-213.36" y1="17.78" x2="-213.36" y2="7.62" width="0.1524" layer="91" grouprefs="NOISE1"/>
<wire x1="-213.36" y1="7.62" x2="-236.22" y2="7.62" width="0.1524" layer="91" grouprefs="NOISE1"/>
<label x="-236.22" y="5.08" size="1.778" layer="95" grouprefs="NOISE1"/>
</segment>
<segment>
<pinref part="U7" gate="G$1" pin="VEE"/>
<wire x1="-182.88" y1="20.32" x2="-182.88" y2="10.16" width="0.1524" layer="91" grouprefs="NOISE1"/>
<wire x1="-182.88" y1="10.16" x2="-162.56" y2="10.16" width="0.1524" layer="91" grouprefs="NOISE1"/>
<label x="-180.34" y="10.16" size="1.778" layer="95" grouprefs="NOISE1"/>
</segment>
<segment>
<wire x1="-210.82" y1="73.66" x2="-241.3" y2="73.66" width="0.1524" layer="91" grouprefs="NOISE1"/>
<label x="-241.3" y="76.2" size="1.778" layer="95" grouprefs="NOISE1"/>
<pinref part="R17" gate="G$1" pin="P1"/>
<pinref part="C10" gate="G$1" pin="PIN_GND"/>
<wire x1="-210.82" y1="73.66" x2="-177.8" y2="73.66" width="0.1524" layer="91" grouprefs="NOISE1"/>
<wire x1="-177.8" y1="73.66" x2="-177.8" y2="78.74" width="0.1524" layer="91" grouprefs="NOISE1"/>
<junction x="-210.82" y="73.66" grouprefs="NOISE1"/>
</segment>
<segment>
<pinref part="C7" gate="G$1" pin="PIN_GND"/>
<wire x1="-248.92" y1="121.92" x2="-210.82" y2="121.92" width="0.1524" layer="91" grouprefs="NOISE1"/>
<label x="-251.46" y="121.92" size="1.778" layer="95" grouprefs="NOISE1"/>
</segment>
<segment>
<pinref part="U8" gate="G$1" pin="GND1"/>
<wire x1="-134.62" y1="243.84" x2="-116.84" y2="243.84" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<label x="-129.54" y="243.84" size="1.778" layer="95" grouprefs="ATMEGA1"/>
</segment>
<segment>
<pinref part="U8" gate="G$1" pin="GND"/>
<wire x1="-175.26" y1="241.3" x2="-198.12" y2="241.3" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<label x="-200.66" y="241.3" size="1.778" layer="95" grouprefs="ATMEGA1"/>
</segment>
<segment>
<wire x1="-195.58" y1="276.86" x2="-215.9" y2="276.86" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<label x="-215.9" y="276.86" size="1.778" layer="95" grouprefs="ATMEGA1"/>
<pinref part="C9" gate="G$1" pin="P$1"/>
</segment>
<segment>
<pinref part="J10" gate="G$1" pin="GND"/>
<pinref part="J10" gate="G$1" pin="GND1"/>
<wire x1="-91.44" y1="215.9" x2="-91.44" y2="213.36" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<wire x1="-91.44" y1="213.36" x2="-71.12" y2="213.36" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<junction x="-91.44" y="213.36" grouprefs="ATMEGA1"/>
<label x="-88.9" y="213.36" size="1.778" layer="95" grouprefs="ATMEGA1"/>
</segment>
</net>
<net name="I2C_SDA" class="0">
<segment>
<wire x1="-134.62" y1="256.54" x2="-119.38" y2="256.54" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<label x="-129.54" y="256.54" size="1.778" layer="95" grouprefs="ATMEGA1"/>
<pinref part="U8" gate="G$1" pin="PC4"/>
</segment>
<segment>
<wire x1="-266.7" y1="322.58" x2="-266.7" y2="340.36" width="0.1524" layer="91" grouprefs="BME_280_TEMP_HUM1"/>
<wire x1="-266.7" y1="340.36" x2="-254" y2="340.36" width="0.1524" layer="91" grouprefs="BME_280_TEMP_HUM1"/>
<label x="-266.7" y="322.58" size="1.778" layer="95" grouprefs="BME_280_TEMP_HUM1"/>
<pinref part="U5" gate="G$1" pin="SDA"/>
</segment>
<segment>
<wire x1="-149.86" y1="340.36" x2="-160.02" y2="340.36" width="0.1524" layer="91" grouprefs="GY-SGP1"/>
<wire x1="-160.02" y1="340.36" x2="-160.02" y2="327.66" width="0.1524" layer="91" grouprefs="GY-SGP1"/>
<wire x1="-160.02" y1="327.66" x2="-175.26" y2="327.66" width="0.1524" layer="91" grouprefs="GY-SGP1"/>
<label x="-175.26" y="327.66" size="1.778" layer="95" grouprefs="GY-SGP1"/>
<pinref part="U9" gate="G$1" pin="SDA"/>
</segment>
</net>
<net name="I2C_SCL" class="0">
<segment>
<wire x1="-119.38" y1="259.08" x2="-134.62" y2="259.08" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<label x="-129.54" y="259.08" size="1.778" layer="95" grouprefs="ATMEGA1"/>
<pinref part="U8" gate="G$1" pin="PC5"/>
</segment>
<segment>
<wire x1="-279.4" y1="325.12" x2="-279.4" y2="342.9" width="0.1524" layer="91" grouprefs="BME_280_TEMP_HUM1"/>
<wire x1="-279.4" y1="342.9" x2="-254" y2="342.9" width="0.1524" layer="91" grouprefs="BME_280_TEMP_HUM1"/>
<label x="-289.56" y="325.12" size="1.778" layer="95" grouprefs="BME_280_TEMP_HUM1"/>
<pinref part="U5" gate="G$1" pin="SCL"/>
</segment>
<segment>
<wire x1="-149.86" y1="342.9" x2="-165.1" y2="342.9" width="0.1524" layer="91" grouprefs="GY-SGP1"/>
<wire x1="-165.1" y1="342.9" x2="-165.1" y2="335.28" width="0.1524" layer="91" grouprefs="GY-SGP1"/>
<wire x1="-165.1" y1="335.28" x2="-175.26" y2="335.28" width="0.1524" layer="91" grouprefs="GY-SGP1"/>
<label x="-175.26" y="332.74" size="1.778" layer="95" grouprefs="GY-SGP1"/>
<pinref part="U9" gate="G$1" pin="SCL"/>
</segment>
</net>
<net name="NOISE_LEVEL" class="0">
<segment>
<wire x1="-134.62" y1="248.92" x2="-109.22" y2="248.92" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<label x="-124.46" y="248.92" size="1.778" layer="95" grouprefs="ATMEGA1"/>
<pinref part="U8" gate="G$1" pin="PC1"/>
</segment>
<segment>
<pinref part="U7" gate="G$1" pin="B_OUT"/>
<wire x1="-162.56" y1="25.4" x2="-152.4" y2="25.4" width="0.1524" layer="91" grouprefs="NOISE1"/>
<wire x1="-152.4" y1="25.4" x2="-152.4" y2="30.48" width="0.1524" layer="91" grouprefs="NOISE1"/>
<pinref part="R23" gate="G$1" pin="P2"/>
<wire x1="-152.4" y1="30.48" x2="-147.32" y2="30.48" width="0.1524" layer="91" grouprefs="NOISE1"/>
<wire x1="-147.32" y1="30.48" x2="-127" y2="30.48" width="0.1524" layer="91" grouprefs="NOISE1"/>
<junction x="-147.32" y="30.48" grouprefs="NOISE1"/>
<label x="-142.24" y="33.02" size="1.778" layer="95" grouprefs="NOISE1"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="BM1" gate="G$1" pin="P$2"/>
<pinref part="C8" gate="G$1" pin="P$1"/>
<wire x1="-213.36" y1="22.86" x2="-208.28" y2="22.86" width="0.1524" layer="91" grouprefs="NOISE1"/>
<pinref part="R18" gate="G$1" pin="P$2"/>
<wire x1="-208.28" y1="22.86" x2="-205.74" y2="22.86" width="0.1524" layer="91" grouprefs="NOISE1"/>
<wire x1="-208.28" y1="24.13" x2="-208.28" y2="22.86" width="0.1524" layer="91" grouprefs="NOISE1"/>
<junction x="-208.28" y="22.86" grouprefs="NOISE1"/>
</segment>
</net>
<net name="N$15" class="0">
<segment>
<pinref part="C8" gate="G$1" pin="P$2"/>
<pinref part="U7" gate="G$1" pin="A+"/>
<wire x1="-190.5" y1="22.86" x2="-182.88" y2="22.86" width="0.1524" layer="91" grouprefs="NOISE1"/>
<pinref part="R19" gate="G$1" pin="P$2"/>
<wire x1="-190.5" y1="22.86" x2="-190.5" y2="19.05" width="0.1524" layer="91" grouprefs="NOISE1"/>
<junction x="-190.5" y="22.86" grouprefs="NOISE1"/>
</segment>
</net>
<net name="N$20" class="0">
<segment>
<pinref part="U7" gate="G$1" pin="B+"/>
<wire x1="-157.48" y1="43.18" x2="-157.48" y2="20.32" width="0.1524" layer="91" grouprefs="NOISE1"/>
<wire x1="-157.48" y1="20.32" x2="-162.56" y2="20.32" width="0.1524" layer="91" grouprefs="NOISE1"/>
<pinref part="C11" gate="G$1" pin="P$2"/>
<wire x1="-162.56" y1="43.18" x2="-157.48" y2="43.18" width="0.1524" layer="91" grouprefs="NOISE1"/>
<pinref part="R22" gate="G$1" pin="P$1"/>
<junction x="-157.48" y="43.18" grouprefs="NOISE1"/>
</segment>
</net>
<net name="N$21" class="0">
<segment>
<pinref part="U7" gate="G$1" pin="A-"/>
<pinref part="R20" gate="G$1" pin="P3"/>
<wire x1="-182.88" y1="25.4" x2="-190.5" y2="25.4" width="0.1524" layer="91" grouprefs="NOISE1"/>
<wire x1="-190.5" y1="25.4" x2="-190.5" y2="53.34" width="0.1524" layer="91" grouprefs="NOISE1"/>
</segment>
</net>
<net name="OUT" class="0">
<segment>
<pinref part="U6" gate="G$1" pin="OUT"/>
<pinref part="L3" gate="G$1" pin="P$1"/>
<wire x1="-213.36" y1="91.44" x2="-210.82" y2="91.44" width="0.1524" layer="91" grouprefs="NOISE1"/>
<pinref part="R17" gate="G$1" pin="P2"/>
<wire x1="-210.82" y1="91.44" x2="-198.12" y2="91.44" width="0.1524" layer="91" grouprefs="NOISE1"/>
<wire x1="-210.82" y1="88.9" x2="-210.82" y2="91.44" width="0.1524" layer="91" grouprefs="NOISE1"/>
<junction x="-210.82" y="91.44" grouprefs="NOISE1"/>
</segment>
</net>
<net name="OUTDOOR_DATA_OUT" class="0">
<segment>
<wire x1="-289.56" y1="238.76" x2="-261.62" y2="238.76" width="0.1524" layer="91" grouprefs="INPUT_CONNECTOR"/>
<label x="-281.94" y="238.76" size="1.778" layer="95" grouprefs="INPUT_CONNECTOR"/>
<pinref part="J3" gate="G$1" pin="PIN"/>
</segment>
<segment>
<pinref part="U8" gate="G$1" pin="PC3"/>
<wire x1="-134.62" y1="254" x2="-109.22" y2="254" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<label x="-134.62" y="254" size="1.778" layer="95" grouprefs="ATMEGA1"/>
</segment>
</net>
<net name="N$17" class="0">
<segment>
<pinref part="U6" gate="G$1" pin="GND"/>
<pinref part="R17" gate="G$1" pin="P3"/>
<wire x1="-223.52" y1="81.28" x2="-218.44" y2="81.28" width="0.1524" layer="91" grouprefs="NOISE1"/>
</segment>
</net>
<net name="N$18" class="0">
<segment>
<pinref part="U7" gate="G$1" pin="A_OUT"/>
<pinref part="R20" gate="G$1" pin="P1"/>
<wire x1="-182.88" y1="45.72" x2="-182.88" y2="43.18" width="0.1524" layer="91" grouprefs="NOISE1"/>
<pinref part="C11" gate="G$1" pin="P$1"/>
<wire x1="-182.88" y1="43.18" x2="-182.88" y2="27.94" width="0.1524" layer="91" grouprefs="NOISE1"/>
<wire x1="-177.8" y1="43.18" x2="-182.88" y2="43.18" width="0.1524" layer="91" grouprefs="NOISE1"/>
<junction x="-182.88" y="43.18" grouprefs="NOISE1"/>
</segment>
</net>
<net name="OUTDOOR_MIDDLEPOINT" class="0">
<segment>
<pinref part="L3" gate="G$1" pin="P$2"/>
<pinref part="C10" gate="G$1" pin="PIN_PLUS"/>
<wire x1="-193.04" y1="91.44" x2="-177.8" y2="91.44" width="0.1524" layer="91" grouprefs="NOISE1"/>
<wire x1="-177.8" y1="91.44" x2="-152.4" y2="91.44" width="0.1524" layer="91" grouprefs="NOISE1"/>
<junction x="-177.8" y="91.44" grouprefs="NOISE1"/>
<label x="-167.64" y="88.9" size="1.778" layer="95" grouprefs="NOISE1"/>
</segment>
<segment>
<pinref part="R20" gate="G$1" pin="P2"/>
<wire x1="-182.88" y1="60.96" x2="-157.48" y2="60.96" width="0.1524" layer="91" grouprefs="NOISE1"/>
<pinref part="R22" gate="G$1" pin="P$2"/>
<wire x1="-157.48" y1="60.96" x2="-157.48" y2="59.69" width="0.1524" layer="91" grouprefs="NOISE1"/>
<wire x1="-182.88" y1="60.96" x2="-213.36" y2="60.96" width="0.1524" layer="91" grouprefs="NOISE1"/>
<junction x="-182.88" y="60.96" grouprefs="NOISE1"/>
<label x="-218.44" y="60.96" size="1.778" layer="95" grouprefs="NOISE1"/>
</segment>
<segment>
<pinref part="R19" gate="G$1" pin="P$1"/>
<wire x1="-190.5" y1="2.54" x2="-172.72" y2="2.54" width="0.1524" layer="91" grouprefs="NOISE1"/>
<label x="-187.96" y="0" size="1.778" layer="95" grouprefs="NOISE1"/>
</segment>
<segment>
<pinref part="R23" gate="G$1" pin="P1"/>
<wire x1="-147.32" y1="15.24" x2="-147.32" y2="12.7" width="0.1524" layer="91" grouprefs="NOISE1"/>
<wire x1="-147.32" y1="12.7" x2="-129.54" y2="12.7" width="0.1524" layer="91" grouprefs="NOISE1"/>
<label x="-152.4" y="10.16" size="1.778" layer="95" grouprefs="NOISE1"/>
</segment>
</net>
<net name="N$19" class="0">
<segment>
<pinref part="U7" gate="G$1" pin="B-"/>
<pinref part="R23" gate="G$1" pin="P3"/>
<wire x1="-162.56" y1="22.86" x2="-154.94" y2="22.86" width="0.1524" layer="91" grouprefs="NOISE1"/>
</segment>
</net>
<net name="OUTDOOR_+5V_F" class="0">
<segment>
<pinref part="L2" gate="G$1" pin="P$2"/>
<pinref part="C7" gate="G$1" pin="PIN_PLUS"/>
<wire x1="-218.44" y1="134.62" x2="-210.82" y2="134.62" width="0.1524" layer="91" grouprefs="NOISE1"/>
<wire x1="-210.82" y1="134.62" x2="-185.42" y2="134.62" width="0.1524" layer="91" grouprefs="NOISE1"/>
<junction x="-210.82" y="134.62" grouprefs="NOISE1"/>
<label x="-208.28" y="134.62" size="1.778" layer="95" grouprefs="NOISE1"/>
</segment>
<segment>
<pinref part="U6" gate="G$1" pin="IN"/>
<wire x1="-233.68" y1="91.44" x2="-241.3" y2="91.44" width="0.1524" layer="91" grouprefs="NOISE1"/>
<label x="-251.46" y="91.44" size="1.778" layer="95" grouprefs="NOISE1"/>
</segment>
<segment>
<pinref part="R18" gate="G$1" pin="P$1"/>
<wire x1="-208.28" y1="40.64" x2="-208.28" y2="45.72" width="0.1524" layer="91" grouprefs="NOISE1"/>
<wire x1="-208.28" y1="45.72" x2="-226.06" y2="45.72" width="0.1524" layer="91" grouprefs="NOISE1"/>
<label x="-228.6" y="45.72" size="1.778" layer="95" grouprefs="NOISE1"/>
</segment>
<segment>
<pinref part="U7" gate="G$1" pin="VCC"/>
<wire x1="-162.56" y1="27.94" x2="-162.56" y2="33.02" width="0.1524" layer="91" grouprefs="NOISE1"/>
<wire x1="-162.56" y1="33.02" x2="-180.34" y2="33.02" width="0.1524" layer="91" grouprefs="NOISE1"/>
<label x="-180.34" y="33.02" size="1.778" layer="95" grouprefs="NOISE1"/>
</segment>
</net>
<net name="N$24" class="0">
<segment>
<pinref part="U8" gate="G$1" pin="PB3"/>
<pinref part="J10" gate="G$1" pin="MOSI"/>
<wire x1="-134.62" y1="231.14" x2="-111.76" y2="231.14" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<wire x1="-111.76" y1="231.14" x2="-111.76" y2="223.52" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
</segment>
</net>
<net name="N$25" class="0">
<segment>
<pinref part="U8" gate="G$1" pin="PB4"/>
<wire x1="-134.62" y1="233.68" x2="-132.08" y2="233.68" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<wire x1="-132.08" y1="233.68" x2="-132.08" y2="213.36" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<pinref part="J10" gate="G$1" pin="MISO"/>
<wire x1="-132.08" y1="213.36" x2="-111.76" y2="213.36" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
</segment>
</net>
<net name="N$26" class="0">
<segment>
<pinref part="U8" gate="G$1" pin="PB5"/>
<wire x1="-134.62" y1="236.22" x2="-129.54" y2="236.22" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<wire x1="-129.54" y1="236.22" x2="-129.54" y2="215.9" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<pinref part="J10" gate="G$1" pin="SCK"/>
<wire x1="-129.54" y1="215.9" x2="-111.76" y2="215.9" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
</segment>
</net>
<net name="ATMEGA_RESET" class="0">
<segment>
<pinref part="J10" gate="G$1" pin="RESET"/>
<wire x1="-111.76" y1="218.44" x2="-127" y2="218.44" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<label x="-127" y="218.44" size="1.778" layer="95" grouprefs="ATMEGA1"/>
</segment>
<segment>
<wire x1="-180.34" y1="276.86" x2="-175.26" y2="276.86" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<pinref part="R21" gate="G$1" pin="P$1"/>
<junction x="-175.26" y="276.86" grouprefs="ATMEGA1"/>
<pinref part="C9" gate="G$1" pin="P$2"/>
<wire x1="-215.9" y1="269.24" x2="-175.26" y2="269.24" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<wire x1="-175.26" y1="269.24" x2="-175.26" y2="276.86" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<label x="-215.9" y="269.24" size="1.778" layer="95" grouprefs="ATMEGA1"/>
<pinref part="U8" gate="G$1" pin="PC6"/>
<wire x1="-175.26" y1="259.08" x2="-175.26" y2="269.24" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<junction x="-175.26" y="269.24" grouprefs="ATMEGA1"/>
</segment>
</net>
<net name="ATMEGA_TXD" class="0">
<segment>
<pinref part="J10" gate="G$1" pin="TXD"/>
<wire x1="-91.44" y1="220.98" x2="-71.12" y2="220.98" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<label x="-86.36" y="220.98" size="1.778" layer="95" grouprefs="ATMEGA1"/>
</segment>
<segment>
<pinref part="U8" gate="G$1" pin="PD0"/>
<wire x1="-175.26" y1="256.54" x2="-213.36" y2="256.54" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<label x="-213.36" y="256.54" size="1.778" layer="95" grouprefs="ATMEGA1"/>
</segment>
</net>
<net name="ATMEGA_RXD" class="0">
<segment>
<pinref part="J10" gate="G$1" pin="RXD"/>
<wire x1="-91.44" y1="218.44" x2="-71.12" y2="218.44" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<label x="-86.36" y="218.44" size="1.778" layer="95" grouprefs="ATMEGA1"/>
</segment>
<segment>
<pinref part="U8" gate="G$1" pin="PD1"/>
<wire x1="-175.26" y1="254" x2="-213.36" y2="254" width="0.1524" layer="91" grouprefs="ATMEGA1"/>
<label x="-213.36" y="254" size="1.778" layer="95" grouprefs="ATMEGA1"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
<errors>
<approved hash="102,1,-254,345.44,GND,OUTDOOR_GND,,,,"/>
<approved hash="102,1,-254,347.98,VCC,OUTDOOR_+5V,,,,"/>
<approved hash="102,1,-149.86,345.44,GND,OUTDOOR_GND,,,,"/>
<approved hash="104,1,-149.86,347.98,U9,VIN,OUTDOOR_+5V,,,"/>
<approved hash="104,1,-182.88,20.32,U7,VEE,OUTDOOR_GND,,,"/>
<approved hash="104,1,-162.56,27.94,U7,VCC,OUTDOOR_+5V_F,,,"/>
<approved hash="104,1,-233.68,91.44,U6,IN,OUTDOOR_+5V_F,,,"/>
<approved hash="104,1,-223.52,81.28,U6,GND,N$17,,,"/>
<approved hash="104,1,-175.26,241.3,U8,GND,OUTDOOR_GND,,,"/>
<approved hash="104,1,-175.26,243.84,U8,VCC,OUTDOOR_+5V,,,"/>
<approved hash="104,1,-134.62,243.84,U8,GND1,OUTDOOR_GND,,,"/>
<approved hash="104,1,-134.62,238.76,U8,AVCC,OUTDOOR_+5V,,,"/>
<approved hash="104,1,-91.44,223.52,J10,VCC,OUTDOOR_+5V,,,"/>
<approved hash="104,1,-91.44,215.9,J10,GND,OUTDOOR_GND,,,"/>
<approved hash="104,1,-91.44,213.36,J10,GND1,OUTDOOR_GND,,,"/>
</errors>
</schematic>
</drawing>
<compatibility>
<note version="6.3" minversion="6.2.2" severity="warning">
Since Version 6.2.2 text objects can contain more than one line,
which will not be processed correctly with this version.
</note>
<note version="9.5" severity="warning">
Since Version 9.5, EAGLE supports persistent groups with
schematics, and board files. Those persistent groups
will not be understood (or retained) with this version.
</note>
</compatibility>
</eagle>
