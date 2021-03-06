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
<text x="-3.81" y="0" size="1.27" layer="21">&gt;NAME</text>
</package>
<package name="TRANSISTOR">
<pad name="B" x="1.27" y="1.27" drill="0.8" shape="square"/>
<pad name="E" x="1.27" y="-1.27" drill="0.8" shape="square"/>
<pad name="C" x="1.27" y="3.81" drill="0.8" shape="square"/>
<wire x1="3.81" y1="-1.27" x2="3.81" y2="3.81" width="0.127" layer="21" curve="-270"/>
<wire x1="3.81" y1="3.81" x2="3.81" y2="-1.27" width="0.127" layer="21"/>
<text x="-0.635" y="3.175" size="0.8128" layer="21">C</text>
<text x="-0.635" y="0.9525" size="0.8128" layer="21">B</text>
<text x="-0.635" y="-1.27" size="0.8128" layer="21">E</text>
<text x="5.08" y="2.54" size="1.27" layer="21">&gt;NAME</text>
</package>
<package name="SWITCH">
<pad name="P$1" x="-1.27" y="0" drill="1.2" shape="square"/>
<pad name="P$2" x="1.27" y="0" drill="1.2" shape="square"/>
<wire x1="-3.81" y1="2.54" x2="-3.81" y2="-2.54" width="0.127" layer="21"/>
<wire x1="-3.81" y1="-2.54" x2="3.81" y2="-2.54" width="0.127" layer="21"/>
<wire x1="3.81" y1="-2.54" x2="3.81" y2="2.54" width="0.127" layer="21"/>
<wire x1="3.81" y1="2.54" x2="-3.81" y2="2.54" width="0.127" layer="21"/>
<text x="-2.54" y="3.81" size="1.27" layer="21">&gt;NAME</text>
</package>
<package name="HALL_SENSOR">
<pad name="VCC" x="0" y="2.54" drill="0.8" shape="square"/>
<pad name="GND" x="0" y="0" drill="0.8" shape="square"/>
<pad name="OUT" x="0" y="-2.54" drill="0.8" shape="square"/>
<wire x1="-0.254" y1="3.81" x2="-1.524" y2="2.54" width="0.127" layer="21"/>
<wire x1="1.27" y1="-3.81" x2="1.27" y2="3.81" width="0.127" layer="21"/>
<wire x1="1.27" y1="3.81" x2="-0.254" y2="3.81" width="0.127" layer="21"/>
<text x="-0.635" y="1.3335" size="0.3048" layer="21">VCC</text>
<text x="-0.635" y="-1.2065" size="0.3048" layer="21">GND</text>
<text x="-0.635" y="-1.651" size="0.3048" layer="21">OUT</text>
<wire x1="1.27" y1="-3.81" x2="-0.254" y2="-3.81" width="0.127" layer="21"/>
<wire x1="-0.254" y1="-3.81" x2="-1.524" y2="-2.794" width="0.127" layer="21"/>
<wire x1="-1.524" y1="2.54" x2="-1.524" y2="-2.794" width="0.127" layer="21"/>
<text x="-8.89" y="0" size="1.27" layer="21">&gt;NAME</text>
</package>
<package name="DIP14">
<pad name="PIN_4" x="-4.064" y="0" drill="0.8" shape="square"/>
<pad name="PIN_3" x="-4.064" y="2.54" drill="0.8" shape="square"/>
<pad name="PIN_5" x="-4.064" y="-2.54" drill="0.8" shape="square"/>
<pad name="PIN_2" x="-4.064" y="5.08" drill="0.8" shape="square"/>
<pad name="PIN_6" x="-4.064" y="-5.08" drill="0.8" shape="square"/>
<pad name="PIN_1" x="-4.064" y="7.62" drill="0.8" shape="square"/>
<pad name="PIN_7" x="-4.064" y="-7.62" drill="0.8" shape="square"/>
<pad name="PIN_8" x="3.81" y="-7.62" drill="0.8" shape="square"/>
<pad name="PIN_9" x="3.81" y="-5.08" drill="0.8" shape="square"/>
<pad name="PIN_10" x="3.81" y="-2.54" drill="0.8" shape="square"/>
<pad name="PIN_11" x="3.81" y="0" drill="0.8" shape="square"/>
<pad name="PIN_12" x="3.81" y="2.54" drill="0.8" shape="square"/>
<pad name="PIN_13" x="3.81" y="5.08" drill="0.8" shape="square"/>
<pad name="PIN_14" x="3.81" y="7.62" drill="0.8" shape="square"/>
<circle x="-1.2192" y="8.2296" radius="0.43105" width="0.127" layer="21"/>
<wire x1="-5.08" y1="9.144" x2="-5.08" y2="-8.636" width="0.127" layer="21"/>
<wire x1="-5.08" y1="-8.636" x2="4.826" y2="-8.636" width="0.127" layer="21"/>
<wire x1="4.826" y1="-8.636" x2="4.826" y2="9.144" width="0.127" layer="21"/>
<wire x1="4.826" y1="9.144" x2="-5.08" y2="9.144" width="0.127" layer="21"/>
<text x="-3.81" y="10.16" size="1.27" layer="21">&gt;NAME</text>
</package>
<package name="LD">
<pad name="PIN_CATHODE" x="-1.27" y="0" drill="0.8" shape="square"/>
<pad name="PIN_ANODE" x="1.27" y="0" drill="0.8" shape="square"/>
<circle x="0" y="0" radius="3.81" width="0.127" layer="21"/>
<wire x1="-0.635" y1="-1.27" x2="-0.635" y2="-1.905" width="0.127" layer="21"/>
<wire x1="-0.635" y1="-1.905" x2="-0.635" y2="-2.54" width="0.127" layer="21"/>
<wire x1="-0.635" y1="-1.27" x2="0.635" y2="-1.905" width="0.127" layer="21"/>
<wire x1="-0.635" y1="-2.54" x2="0.635" y2="-1.905" width="0.127" layer="21"/>
<wire x1="0.635" y1="-1.905" x2="0.635" y2="-1.27" width="0.127" layer="21"/>
<wire x1="0.635" y1="-1.905" x2="0.635" y2="-2.54" width="0.127" layer="21"/>
<wire x1="0.635" y1="-1.905" x2="1.27" y2="-1.905" width="0.127" layer="21"/>
<wire x1="-1.27" y1="-1.905" x2="-0.635" y2="-1.905" width="0.127" layer="21"/>
<text x="-2.54" y="3.81" size="1.27" layer="21">&gt;NAME</text>
</package>
<package name="SB-NO-SPST-ANGLE">
<pad name="NC1" x="-3.556" y="2.54" drill="1.5" shape="square"/>
<pad name="NC2" x="3.556" y="2.54" drill="1.5" shape="square"/>
<pad name="A" x="-2.286" y="0" drill="1.2" shape="square"/>
<pad name="B" x="2.286" y="0" drill="1.2" shape="square"/>
<wire x1="-5.334" y1="4.064" x2="5.334" y2="4.064" width="0.127" layer="21"/>
<wire x1="-5.334" y1="4.064" x2="-5.334" y2="-2.54" width="0.127" layer="21"/>
<wire x1="-5.334" y1="-2.54" x2="5.334" y2="-2.54" width="0.127" layer="21"/>
<wire x1="5.334" y1="-2.54" x2="5.334" y2="4.064" width="0.127" layer="21"/>
<text x="-1.778" y="-2.032" size="0.8128" layer="21">FRONT</text>
<text x="-3.81" y="5.08" size="1.27" layer="21">&gt;NAME</text>
</package>
<package name="ESP32">
<pad name="IO26" x="-12.7" y="0" drill="0.8" shape="square"/>
<pad name="IO5" x="12.7" y="0" drill="0.8" shape="square"/>
<pad name="IO25" x="-12.7" y="2.54" drill="0.8" shape="square"/>
<pad name="IO33" x="-12.7" y="5.08" drill="0.8" shape="square"/>
<pad name="IO32" x="-12.7" y="7.62" drill="0.8" shape="square"/>
<pad name="IO35" x="-12.7" y="10.16" drill="0.8" shape="square"/>
<pad name="IO34" x="-12.7" y="12.7" drill="0.8" shape="square"/>
<pad name="SVN" x="-12.7" y="15.24" drill="0.8" shape="square"/>
<pad name="SVP" x="-12.7" y="17.78" drill="0.8" shape="square"/>
<pad name="EN" x="-12.7" y="20.32" drill="0.8" shape="square"/>
<pad name="3V3" x="-12.7" y="22.86" drill="0.8" shape="square"/>
<pad name="IO27" x="-12.7" y="-2.54" drill="0.8" shape="square"/>
<pad name="IO14" x="-12.7" y="-5.08" drill="0.8" shape="square"/>
<pad name="IO12" x="-12.7" y="-7.62" drill="0.8" shape="square"/>
<pad name="GND_2" x="-12.7" y="-10.16" drill="0.8" shape="square"/>
<pad name="IO13" x="-12.7" y="-12.7" drill="0.8" shape="square"/>
<pad name="SD2" x="-12.7" y="-15.24" drill="0.8" shape="square"/>
<pad name="SD3" x="-12.7" y="-17.78" drill="0.8" shape="square"/>
<pad name="CMD" x="-12.7" y="-20.32" drill="0.8" shape="square"/>
<pad name="+5V" x="-12.7" y="-22.86" drill="0.8" shape="square"/>
<pad name="GND" x="12.7" y="22.86" drill="0.8" shape="square"/>
<pad name="IO23" x="12.7" y="20.32" drill="0.8" shape="square"/>
<pad name="IO22" x="12.7" y="17.78" drill="0.8" shape="square"/>
<pad name="TXD0" x="12.7" y="15.24" drill="0.8" shape="square"/>
<pad name="RXD" x="12.7" y="12.7" drill="0.8" shape="square"/>
<pad name="GND_1" x="12.7" y="7.62" drill="0.8" shape="square"/>
<pad name="IO21" x="12.7" y="10.16" drill="0.8" shape="square"/>
<pad name="IO19" x="12.7" y="5.08" drill="0.8" shape="square"/>
<pad name="IO18" x="12.7" y="2.54" drill="0.8" shape="square"/>
<pad name="IO16" x="12.7" y="-5.08" drill="0.8" shape="square"/>
<pad name="IO17" x="12.7" y="-2.54" drill="0.8" shape="square"/>
<pad name="IO4" x="12.7" y="-7.62" drill="0.8" shape="square"/>
<pad name="IO0" x="12.7" y="-10.16" drill="0.8" shape="square"/>
<pad name="IO2" x="12.7" y="-12.7" drill="0.8" shape="square"/>
<pad name="SD1" x="12.7" y="-17.78" drill="0.8" shape="square"/>
<pad name="IO15" x="12.7" y="-15.24" drill="0.8" shape="square"/>
<pad name="SD0" x="12.7" y="-20.32" drill="0.8" shape="square"/>
<pad name="CLK" x="12.7" y="-22.86" drill="0.8" shape="square"/>
<wire x1="-15.24" y1="25.4" x2="-7.62" y2="25.4" width="0.127" layer="21"/>
<wire x1="-7.62" y1="25.4" x2="7.62" y2="25.4" width="0.127" layer="21"/>
<wire x1="7.62" y1="25.4" x2="15.24" y2="25.4" width="0.127" layer="21"/>
<wire x1="15.24" y1="25.4" x2="15.24" y2="-25.4" width="0.127" layer="21"/>
<wire x1="15.24" y1="-25.4" x2="2.54" y2="-25.4" width="0.127" layer="21"/>
<wire x1="2.54" y1="-25.4" x2="-2.54" y2="-25.4" width="0.127" layer="21"/>
<wire x1="-2.54" y1="-25.4" x2="-15.24" y2="-25.4" width="0.127" layer="21"/>
<wire x1="-15.24" y1="-25.4" x2="-15.24" y2="25.4" width="0.127" layer="21"/>
<wire x1="-7.62" y1="30.48" x2="-7.62" y2="25.4" width="0.127" layer="21"/>
<wire x1="-7.62" y1="30.48" x2="7.62" y2="30.48" width="0.127" layer="21"/>
<wire x1="7.62" y1="25.4" x2="7.62" y2="30.48" width="0.127" layer="21"/>
<wire x1="-2.54" y1="-25.4" x2="-2.54" y2="-22.86" width="0.127" layer="21"/>
<wire x1="-2.54" y1="-22.86" x2="2.54" y2="-22.86" width="0.127" layer="21"/>
<wire x1="2.54" y1="-22.86" x2="2.54" y2="-25.4" width="0.127" layer="21"/>
<text x="-3.81" y="3.81" size="1.9304" layer="21">ESP32</text>
<text x="-11.43" y="22.86" size="0.8128" layer="21">3V3</text>
<text x="-11.43" y="20.32" size="0.8128" layer="21">EN</text>
<text x="-11.43" y="17.78" size="0.8128" layer="21">SVP</text>
<text x="-11.43" y="15.24" size="0.8128" layer="21">SVN</text>
<text x="-11.43" y="12.7" size="0.8128" layer="21">IO34</text>
<text x="-11.43" y="10.16" size="0.8128" layer="21">IO35</text>
<text x="-11.43" y="7.62" size="0.8128" layer="21">IO32</text>
<text x="-11.43" y="5.08" size="0.8128" layer="21">IO33</text>
<text x="-11.43" y="2.54" size="0.8128" layer="21">IO25</text>
<text x="-11.43" y="0" size="0.8128" layer="21">IO26</text>
<text x="-11.43" y="-2.54" size="0.8128" layer="21">IO27</text>
<text x="-11.43" y="-5.08" size="0.8128" layer="21">IO14</text>
<text x="-11.43" y="-7.62" size="0.8128" layer="21">IO12</text>
<text x="-11.43" y="-10.16" size="0.8128" layer="21">GND</text>
<text x="-11.43" y="-12.7" size="0.8128" layer="21">IO13</text>
<text x="-11.43" y="-15.24" size="0.8128" layer="21">SD2</text>
<text x="-11.43" y="-17.78" size="0.8128" layer="21">SD3</text>
<text x="-11.43" y="-20.32" size="0.8128" layer="21">CMD</text>
<text x="-11.43" y="-22.86" size="0.8128" layer="21">+5V</text>
<text x="8.89" y="22.86" size="0.8128" layer="21">GND</text>
<text x="8.89" y="20.32" size="0.8128" layer="21">IO23</text>
<text x="8.89" y="17.78" size="0.8128" layer="21">IO22</text>
<text x="8.89" y="15.24" size="0.8128" layer="21">TXD0</text>
<text x="8.89" y="12.7" size="0.8128" layer="21">RXD0</text>
<text x="8.89" y="10.16" size="0.8128" layer="21">IO21</text>
<text x="8.89" y="7.62" size="0.8128" layer="21">GND</text>
<text x="8.89" y="5.08" size="0.8128" layer="21">IO19</text>
<text x="8.89" y="2.54" size="0.8128" layer="21">IO18</text>
<text x="8.89" y="0" size="0.8128" layer="21">IO5</text>
<text x="8.89" y="-2.54" size="0.8128" layer="21">IO17</text>
<text x="8.89" y="-5.08" size="0.8128" layer="21">IO16</text>
<text x="8.89" y="-7.62" size="0.8128" layer="21">IO4</text>
<text x="8.89" y="-10.16" size="0.8128" layer="21">IO0</text>
<text x="8.89" y="-12.7" size="0.8128" layer="21">IO2</text>
<text x="8.89" y="-15.24" size="0.8128" layer="21">IO15</text>
<text x="8.89" y="-17.78" size="0.8128" layer="21">SD1</text>
<text x="8.89" y="-20.32" size="0.8128" layer="21">SD0</text>
<text x="8.89" y="-22.86" size="0.8128" layer="21">CLK</text>
<text x="-3.81" y="-5.08" size="1.27" layer="21">&gt;NAME</text>
</package>
<package name="RD-3362H">
<pad name="P1" x="-2.54" y="-1.27" drill="0.8" shape="square"/>
<pad name="P3" x="0" y="1.27" drill="0.8" shape="square"/>
<pad name="P2" x="2.54" y="-1.27" drill="0.8" shape="square"/>
<wire x1="-3.81" y1="3.81" x2="-3.81" y2="-3.81" width="0.127" layer="21"/>
<wire x1="3.81" y1="-3.81" x2="3.81" y2="3.81" width="0.127" layer="21"/>
<wire x1="-3.81" y1="-3.81" x2="3.81" y2="-3.81" width="0.127" layer="21"/>
<wire x1="-3.81" y1="3.81" x2="3.81" y2="3.81" width="0.127" layer="21"/>
<text x="-3.81" y="5.08" size="1.27" layer="21">&gt;NAME</text>
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
<text x="-2.54" y="5.08" size="1.27" layer="21">&gt;NAME</text>
</package>
<package name="JST-XH254-4P">
<pad name="PIN2" x="-1.27" y="0" drill="0.8" shape="square"/>
<pad name="PIN3" x="1.27" y="0" drill="0.8" shape="square"/>
<pad name="PIN1" x="-3.81" y="0" drill="0.8" shape="square"/>
<pad name="PIN4" x="3.81" y="0" drill="0.8" shape="square"/>
<wire x1="-6.35" y1="2.54" x2="-6.35" y2="-2.54" width="0.127" layer="21"/>
<wire x1="-6.35" y1="-2.54" x2="6.35" y2="-2.54" width="0.127" layer="21"/>
<wire x1="6.35" y1="-2.54" x2="6.35" y2="2.54" width="0.127" layer="21"/>
<wire x1="6.35" y1="2.54" x2="-6.35" y2="2.54" width="0.127" layer="21"/>
<text x="-2.54" y="-3.81" size="1.27" layer="21">&gt;NAME</text>
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
<symbol name="TRANSISTOR_NPN">
<pin name="B" x="-7.62" y="0" visible="off" length="middle"/>
<pin name="C" x="0" y="7.62" visible="off" length="middle" rot="R270"/>
<pin name="E" x="0" y="-7.62" visible="off" length="middle" rot="R90"/>
<circle x="0" y="0" radius="3.81" width="0.254" layer="94"/>
<wire x1="-2.54" y1="2.54" x2="-2.54" y2="0" width="0.254" layer="94"/>
<wire x1="-2.54" y1="0" x2="-2.54" y2="-2.54" width="0.254" layer="94"/>
<wire x1="0" y1="2.54" x2="-2.54" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="-2.54" x2="-2.54" y2="0" width="0.254" layer="94"/>
<polygon width="0.254" layer="94">
<vertex x="0" y="-2.54"/>
<vertex x="0" y="-1.27"/>
<vertex x="-1.27" y="-2.54"/>
</polygon>
<text x="3.81" y="1.27" size="1.778" layer="94">&gt;NAME</text>
<text x="3.81" y="-2.54" size="1.778" layer="94">&gt;VALUE</text>
</symbol>
<symbol name="SWITCH">
<pin name="P$1" x="-10.16" y="0" visible="off" length="middle"/>
<pin name="P$2" x="10.16" y="0" visible="off" length="middle" rot="R180"/>
<wire x1="-5.08" y1="0" x2="-2.54" y2="0" width="0.254" layer="94"/>
<wire x1="5.08" y1="0" x2="2.54" y2="0" width="0.254" layer="94"/>
<wire x1="-2.54" y1="0" x2="2.54" y2="2.54" width="0.254" layer="94"/>
<text x="-5.08" y="5.08" size="1.778" layer="94">&gt;NAME</text>
<text x="-5.08" y="-5.08" size="1.778" layer="94">&gt;VALUE</text>
</symbol>
<symbol name="HALL_SENSOR">
<pin name="OUT" x="-7.62" y="0" visible="off" length="middle"/>
<pin name="GND" x="0" y="-7.62" visible="off" length="middle" direction="sup" rot="R90"/>
<pin name="VCC" x="0" y="7.62" visible="off" length="middle" direction="sup" rot="R270"/>
<wire x1="-2.54" y1="2.54" x2="-2.54" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-2.54" x2="2.54" y2="-2.54" width="0.254" layer="94"/>
<wire x1="2.54" y1="-2.54" x2="2.54" y2="2.54" width="0.254" layer="94"/>
<wire x1="2.54" y1="2.54" x2="-2.54" y2="2.54" width="0.254" layer="94"/>
<wire x1="-2.54" y1="2.54" x2="2.54" y2="-2.54" width="0.254" layer="94"/>
<wire x1="2.54" y1="2.54" x2="-2.54" y2="-2.54" width="0.254" layer="94"/>
<text x="2.54" y="5.08" size="1.778" layer="94">VCC</text>
<text x="2.54" y="-5.08" size="1.778" layer="94">GND</text>
<text x="-10.16" y="-2.54" size="1.778" layer="94">OUT</text>
<text x="7.62" y="0" size="1.778" layer="94">&gt;NAME</text>
<text x="7.62" y="-2.54" size="1.778" layer="94">&gt;VALUE</text>
</symbol>
<symbol name="SN74LS32N">
<pin name="2Y" x="-10.16" y="-5.08" visible="off" length="middle" direction="out"/>
<pin name="1Y" x="-10.16" y="2.54" visible="off" length="middle" direction="out"/>
<pin name="2A" x="-10.16" y="0" visible="off" length="middle" direction="in"/>
<pin name="1B" x="-10.16" y="5.08" visible="off" length="middle" direction="in"/>
<pin name="2B" x="-10.16" y="-2.54" visible="off" length="middle" direction="in"/>
<pin name="1A" x="-10.16" y="7.62" visible="off" length="middle" direction="in"/>
<pin name="GND" x="-10.16" y="-7.62" visible="off" length="middle" direction="pwr"/>
<pin name="VCC" x="10.16" y="7.62" visible="off" length="middle" direction="pwr" rot="R180"/>
<pin name="4A" x="10.16" y="5.08" visible="off" length="middle" direction="in" rot="R180"/>
<pin name="4B" x="10.16" y="2.54" visible="off" length="middle" direction="in" rot="R180"/>
<pin name="4Y" x="10.16" y="0" visible="off" length="middle" direction="out" rot="R180"/>
<pin name="3A" x="10.16" y="-2.54" visible="off" length="middle" direction="in" rot="R180"/>
<pin name="3B" x="10.16" y="-5.08" visible="off" length="middle" direction="in" rot="R180"/>
<pin name="3Y" x="10.16" y="-7.62" visible="off" length="middle" direction="out" rot="R180"/>
<wire x1="-5.08" y1="10.16" x2="-5.08" y2="-10.16" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-10.16" x2="5.08" y2="-10.16" width="0.254" layer="94"/>
<wire x1="5.08" y1="-10.16" x2="5.08" y2="10.16" width="0.254" layer="94"/>
<wire x1="5.08" y1="10.16" x2="-5.08" y2="10.16" width="0.254" layer="94"/>
<text x="-4.445" y="6.985" size="1.016" layer="94">1A</text>
<text x="-4.445" y="5.08" size="1.016" layer="94">1B</text>
<text x="-4.445" y="2.54" size="1.016" layer="94">1Y</text>
<text x="-4.445" y="-5.08" size="1.016" layer="94">2Y</text>
<text x="-4.445" y="0" size="1.016" layer="94">2A</text>
<text x="-4.445" y="-2.54" size="1.016" layer="94">2B</text>
<text x="-4.445" y="-7.62" size="1.016" layer="94">GND</text>
<text x="1.905" y="6.985" size="1.016" layer="94">VCC</text>
<text x="3.175" y="5.08" size="1.016" layer="94">4A</text>
<text x="3.175" y="2.54" size="1.016" layer="94">4B</text>
<text x="3.175" y="0" size="1.016" layer="94">4Y</text>
<text x="3.175" y="-2.54" size="1.016" layer="94">3A</text>
<text x="3.175" y="-5.08" size="1.016" layer="94">3B</text>
<text x="3.175" y="-7.62" size="1.016" layer="94">3Y</text>
<text x="-5.08" y="12.7" size="1.778" layer="94">&gt;NAME</text>
<text x="-5.08" y="-12.7" size="1.778" layer="94">&gt;VALUE</text>
</symbol>
<symbol name="LD">
<pin name="PIN_CATHODE" x="-7.62" y="0" visible="off" length="middle"/>
<wire x1="-2.54" y1="2.54" x2="-2.54" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-2.54" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="-2.54" y1="2.54" x2="0" y2="0" width="0.254" layer="94"/>
<pin name="PIN_ANODE" x="5.08" y="0" visible="off" length="middle" rot="R180"/>
<wire x1="0" y1="2.54" x2="0" y2="-2.54" width="0.254" layer="94"/>
<wire x1="0.508" y1="3.048" x2="1.524" y2="4.064" width="0.254" layer="94"/>
<polygon width="0.254" layer="94">
<vertex x="1.016" y="4.064"/>
<vertex x="1.524" y="3.556"/>
<vertex x="1.524" y="4.064"/>
</polygon>
<wire x1="-1.016" y1="3.556" x2="0" y2="4.572" width="0.254" layer="94"/>
<polygon width="0.254" layer="94">
<vertex x="-0.508" y="4.572"/>
<vertex x="0" y="4.064"/>
<vertex x="0" y="4.572"/>
</polygon>
<text x="-7.62" y="-5.08" size="1.778" layer="94">&gt;NAME</text>
<text x="-7.62" y="-7.62" size="1.778" layer="94">&gt;VALUE</text>
</symbol>
<symbol name="SB-NO">
<pin name="P$1" x="-10.16" y="0" visible="off" length="middle"/>
<pin name="P$2" x="10.16" y="0" visible="off" length="middle" rot="R180"/>
<wire x1="5.08" y1="0" x2="2.54" y2="0" width="0.254" layer="94"/>
<wire x1="-5.08" y1="0" x2="-2.54" y2="0" width="0.254" layer="94"/>
<wire x1="-2.54" y1="0" x2="0" y2="1.27" width="0.254" layer="94"/>
<wire x1="0" y1="1.27" x2="2.54" y2="2.54" width="0.254" layer="94"/>
<wire x1="0" y1="1.27" x2="0" y2="3.81" width="0.254" layer="94" style="shortdash"/>
<wire x1="-1.27" y1="2.54" x2="-1.27" y2="3.81" width="0.254" layer="94"/>
<wire x1="-1.27" y1="3.81" x2="1.27" y2="3.81" width="0.254" layer="94"/>
<wire x1="1.27" y1="2.54" x2="1.27" y2="3.81" width="0.254" layer="94"/>
<text x="-5.08" y="-2.54" size="1.778" layer="94">&gt;NAME</text>
<text x="-5.08" y="-5.08" size="1.778" layer="94">&gt;VALUE</text>
</symbol>
<symbol name="ESP32">
<pin name="IO26" x="-20.32" y="0" length="middle"/>
<pin name="IO27" x="-20.32" y="-2.54" length="middle"/>
<pin name="IO25" x="-20.32" y="2.54" length="middle"/>
<pin name="IO14" x="-20.32" y="-5.08" length="middle"/>
<pin name="IO33" x="-20.32" y="5.08" length="middle"/>
<pin name="IO12" x="-20.32" y="-7.62" length="middle"/>
<pin name="IO32" x="-20.32" y="7.62" length="middle"/>
<pin name="GND_2" x="-20.32" y="-10.16" length="middle"/>
<pin name="IO35" x="-20.32" y="10.16" length="middle"/>
<pin name="IO13" x="-20.32" y="-12.7" length="middle"/>
<pin name="IO34" x="-20.32" y="12.7" length="middle"/>
<pin name="SD2" x="-20.32" y="-15.24" length="middle"/>
<pin name="SVN" x="-20.32" y="15.24" length="middle"/>
<pin name="SD3" x="-20.32" y="-17.78" length="middle"/>
<pin name="SVP" x="-20.32" y="17.78" length="middle"/>
<pin name="CMD" x="-20.32" y="-20.32" length="middle"/>
<pin name="EN" x="-20.32" y="20.32" length="middle"/>
<pin name="5V" x="-20.32" y="-22.86" length="middle" direction="sup"/>
<pin name="3V3" x="-20.32" y="22.86" length="middle" direction="pwr"/>
<pin name="IO23" x="20.32" y="17.78" length="middle" rot="R180"/>
<pin name="IO22" x="20.32" y="20.32" length="middle" rot="R180"/>
<pin name="TXD0" x="20.32" y="15.24" length="middle" rot="R180"/>
<pin name="GND" x="20.32" y="22.86" length="middle" direction="sup" rot="R180"/>
<pin name="RXD0" x="20.32" y="12.7" length="middle" rot="R180"/>
<pin name="IO21" x="20.32" y="10.16" length="middle" rot="R180"/>
<pin name="GND_1" x="20.32" y="7.62" length="middle" rot="R180"/>
<pin name="IO19" x="20.32" y="5.08" length="middle" rot="R180"/>
<pin name="IO18" x="20.32" y="2.54" length="middle" rot="R180"/>
<pin name="IO5" x="20.32" y="0" length="middle" rot="R180"/>
<pin name="IO17" x="20.32" y="-2.54" length="middle" rot="R180"/>
<pin name="IO16" x="20.32" y="-5.08" length="middle" rot="R180"/>
<pin name="CLK" x="20.32" y="-22.86" length="middle" rot="R180"/>
<pin name="SD0" x="20.32" y="-20.32" length="middle" rot="R180"/>
<pin name="SD1" x="20.32" y="-17.78" length="middle" rot="R180"/>
<pin name="IO15" x="20.32" y="-15.24" length="middle" rot="R180"/>
<pin name="IO2" x="20.32" y="-12.7" length="middle" rot="R180"/>
<pin name="IO0" x="20.32" y="-10.16" length="middle" rot="R180"/>
<pin name="IO4" x="20.32" y="-7.62" length="middle" rot="R180"/>
<wire x1="-15.24" y1="25.4" x2="-15.24" y2="-25.4" width="0.254" layer="94"/>
<wire x1="-15.24" y1="-25.4" x2="-2.54" y2="-25.4" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-25.4" x2="2.54" y2="-25.4" width="0.254" layer="94"/>
<wire x1="2.54" y1="-25.4" x2="15.24" y2="-25.4" width="0.254" layer="94"/>
<wire x1="15.24" y1="-25.4" x2="15.24" y2="25.4" width="0.254" layer="94"/>
<wire x1="15.24" y1="25.4" x2="10.16" y2="25.4" width="0.254" layer="94"/>
<text x="-5.08" y="27.94" size="1.778" layer="94">&gt;NAME</text>
<text x="-5.08" y="-27.94" size="1.778" layer="94">&gt;VALUE</text>
<wire x1="10.16" y1="25.4" x2="-10.16" y2="25.4" width="0.254" layer="94"/>
<wire x1="-10.16" y1="25.4" x2="-15.24" y2="25.4" width="0.254" layer="94"/>
<wire x1="-10.16" y1="25.4" x2="-10.16" y2="30.48" width="0.254" layer="94"/>
<wire x1="-10.16" y1="30.48" x2="10.16" y2="30.48" width="0.254" layer="94"/>
<wire x1="10.16" y1="30.48" x2="10.16" y2="25.4" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-25.4" x2="-2.54" y2="-22.86" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-22.86" x2="2.54" y2="-22.86" width="0.254" layer="94"/>
<wire x1="2.54" y1="-22.86" x2="2.54" y2="-25.4" width="0.254" layer="94"/>
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
<symbol name="JST-XH254-4P">
<pin name="PIN2" x="-5.08" y="2.54" length="middle"/>
<pin name="PIN3" x="-5.08" y="-2.54" length="middle"/>
<pin name="PIN1" x="-5.08" y="7.62" length="middle"/>
<pin name="PIN4" x="-5.08" y="-7.62" length="middle"/>
<wire x1="0" y1="10.16" x2="0" y2="-10.16" width="0.254" layer="94"/>
<wire x1="0" y1="-10.16" x2="10.16" y2="-10.16" width="0.254" layer="94"/>
<wire x1="10.16" y1="-10.16" x2="10.16" y2="10.16" width="0.254" layer="94"/>
<wire x1="10.16" y1="10.16" x2="0" y2="10.16" width="0.254" layer="94"/>
<text x="12.7" y="2.54" size="1.778" layer="94">&gt;NAME</text>
<text x="12.7" y="2.54" size="1.778" layer="94">&gt;NAME</text>
<text x="12.7" y="-2.54" size="1.778" layer="94">&gt;VALUE</text>
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
<deviceset name="TRANSISTOR_NPN" prefix="Q" uservalue="yes">
<gates>
<gate name="G$1" symbol="TRANSISTOR_NPN" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TRANSISTOR">
<connects>
<connect gate="G$1" pin="B" pad="B"/>
<connect gate="G$1" pin="C" pad="C"/>
<connect gate="G$1" pin="E" pad="E"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="SWITCH" prefix="SW">
<gates>
<gate name="G$1" symbol="SWITCH" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SWITCH">
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
<deviceset name="HALL_SENSOR" prefix="B">
<gates>
<gate name="G$1" symbol="HALL_SENSOR" x="0" y="0"/>
</gates>
<devices>
<device name="" package="HALL_SENSOR">
<connects>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="OUT" pad="OUT"/>
<connect gate="G$1" pin="VCC" pad="VCC"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="SN74LS32N" prefix="U">
<gates>
<gate name="G$1" symbol="SN74LS32N" x="0" y="0"/>
</gates>
<devices>
<device name="" package="DIP14">
<connects>
<connect gate="G$1" pin="1A" pad="PIN_1"/>
<connect gate="G$1" pin="1B" pad="PIN_2"/>
<connect gate="G$1" pin="1Y" pad="PIN_3"/>
<connect gate="G$1" pin="2A" pad="PIN_4"/>
<connect gate="G$1" pin="2B" pad="PIN_5"/>
<connect gate="G$1" pin="2Y" pad="PIN_6"/>
<connect gate="G$1" pin="3A" pad="PIN_10"/>
<connect gate="G$1" pin="3B" pad="PIN_9"/>
<connect gate="G$1" pin="3Y" pad="PIN_8"/>
<connect gate="G$1" pin="4A" pad="PIN_13"/>
<connect gate="G$1" pin="4B" pad="PIN_12"/>
<connect gate="G$1" pin="4Y" pad="PIN_11"/>
<connect gate="G$1" pin="GND" pad="PIN_7"/>
<connect gate="G$1" pin="VCC" pad="PIN_14"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="LD" prefix="D">
<gates>
<gate name="G$1" symbol="LD" x="0" y="0"/>
</gates>
<devices>
<device name="" package="LD">
<connects>
<connect gate="G$1" pin="PIN_ANODE" pad="PIN_ANODE"/>
<connect gate="G$1" pin="PIN_CATHODE" pad="PIN_CATHODE"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="SB-NO" prefix="SB">
<gates>
<gate name="G$1" symbol="SB-NO" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SB-NO-SPST-ANGLE">
<connects>
<connect gate="G$1" pin="P$1" pad="A"/>
<connect gate="G$1" pin="P$2" pad="B"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="ESP32" prefix="U">
<gates>
<gate name="G$1" symbol="ESP32" x="0" y="0"/>
</gates>
<devices>
<device name="" package="ESP32">
<connects>
<connect gate="G$1" pin="3V3" pad="3V3"/>
<connect gate="G$1" pin="5V" pad="+5V"/>
<connect gate="G$1" pin="CLK" pad="CLK"/>
<connect gate="G$1" pin="CMD" pad="CMD"/>
<connect gate="G$1" pin="EN" pad="EN"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="GND_1" pad="GND_1"/>
<connect gate="G$1" pin="GND_2" pad="GND_2"/>
<connect gate="G$1" pin="IO0" pad="IO0"/>
<connect gate="G$1" pin="IO12" pad="IO12"/>
<connect gate="G$1" pin="IO13" pad="IO13"/>
<connect gate="G$1" pin="IO14" pad="IO14"/>
<connect gate="G$1" pin="IO15" pad="IO15"/>
<connect gate="G$1" pin="IO16" pad="IO16"/>
<connect gate="G$1" pin="IO17" pad="IO17"/>
<connect gate="G$1" pin="IO18" pad="IO18"/>
<connect gate="G$1" pin="IO19" pad="IO19"/>
<connect gate="G$1" pin="IO2" pad="IO2"/>
<connect gate="G$1" pin="IO21" pad="IO21"/>
<connect gate="G$1" pin="IO22" pad="IO22"/>
<connect gate="G$1" pin="IO23" pad="IO23"/>
<connect gate="G$1" pin="IO25" pad="IO25"/>
<connect gate="G$1" pin="IO26" pad="IO26"/>
<connect gate="G$1" pin="IO27" pad="IO27"/>
<connect gate="G$1" pin="IO32" pad="IO32"/>
<connect gate="G$1" pin="IO33" pad="IO33"/>
<connect gate="G$1" pin="IO34" pad="IO34"/>
<connect gate="G$1" pin="IO35" pad="IO35"/>
<connect gate="G$1" pin="IO4" pad="IO4"/>
<connect gate="G$1" pin="IO5" pad="IO5"/>
<connect gate="G$1" pin="RXD0" pad="RXD"/>
<connect gate="G$1" pin="SD0" pad="SD0"/>
<connect gate="G$1" pin="SD1" pad="SD1"/>
<connect gate="G$1" pin="SD2" pad="SD2"/>
<connect gate="G$1" pin="SD3" pad="SD3"/>
<connect gate="G$1" pin="SVN" pad="SVN"/>
<connect gate="G$1" pin="SVP" pad="SVP"/>
<connect gate="G$1" pin="TXD0" pad="TXD0"/>
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
<deviceset name="JST-XH254-4P" prefix="J">
<gates>
<gate name="G$1" symbol="JST-XH254-4P" x="-5.08" y="0"/>
</gates>
<devices>
<device name="" package="JST-XH254-4P">
<connects>
<connect gate="G$1" pin="PIN1" pad="PIN1"/>
<connect gate="G$1" pin="PIN2" pad="PIN2"/>
<connect gate="G$1" pin="PIN3" pad="PIN3"/>
<connect gate="G$1" pin="PIN4" pad="PIN4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply1" urn="urn:adsk.eagle:library:371">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
 GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
 Please keep in mind, that these devices are necessary for the
 automatic wiring of the supply signals.&lt;p&gt;
 The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
 In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
 &lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="GND" urn="urn:adsk.eagle:symbol:26925/1" library_version="1">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="GND" urn="urn:adsk.eagle:component:26954/1" prefix="GND" library_version="1">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
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
<schematic_group name="OPEN-CLOSE1"/>
<schematic_group name="SERVO_CONTROL1"/>
<schematic_group name="HALL_SENSOR1"/>
<schematic_group name="LED_CONTROL_GROUP1"/>
<schematic_group name="ESP1"/>
<schematic_group name="INPUT_CONNECTORS"/>
</groups>
<parts>
<part name="B1" library="my_devices" deviceset="HALL_SENSOR" device="" value="A3144"/>
<part name="GND10" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="R13" library="my_devices" deviceset="R" device="" value="10K"/>
<part name="GND3" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="SW1" library="my_devices" deviceset="SWITCH" device="" value="MRS-101-2C3-B"/>
<part name="GND4" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="U4" library="my_devices" deviceset="SN74LS32N" device=""/>
<part name="GND20" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="R12" library="my_devices" deviceset="R" device="" value="10K"/>
<part name="D1" library="my_devices" deviceset="LD" device="" value="GNL-3014ED"/>
<part name="Q1" library="my_devices" deviceset="TRANSISTOR_NPN" device="" value="2N3904"/>
<part name="R2" library="my_devices" deviceset="R" device="" value="100"/>
<part name="GND7" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="R1" library="my_devices" deviceset="R" device="" value="620"/>
<part name="SB1" library="my_devices" deviceset="SB-NO" device="" value="FSMRA6JH"/>
<part name="SB2" library="my_devices" deviceset="SB-NO" device="" value="FSMRA6JH"/>
<part name="GND9" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="U1" library="my_devices" deviceset="ESP32" device=""/>
<part name="GND2" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="R4" library="my_devices" deviceset="R" device="" value="620"/>
<part name="R5" library="my_devices" deviceset="R" device="" value="620"/>
<part name="R7" library="my_devices" deviceset="R" device="" value="620"/>
<part name="R8" library="my_devices" deviceset="R" device="" value="620"/>
<part name="R6" library="my_devices" deviceset="RD" device="" value="5K"/>
<part name="GND8" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="J1" library="my_devices" deviceset="JST-XH254-4P" device="" value="JST-XH2.54-4P"/>
<part name="GND5" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
</parts>
<sheets>
<sheet>
<plain>
<text x="-10.16" y="111.76" size="1.778" layer="91">Indoor window control unit</text>
<text x="-76.2" y="193.04" size="1.778" layer="91" grouprefs="ESP1">5V</text>
<text x="-116.84" y="193.04" size="1.778" layer="91" grouprefs="ESP1">3V3</text>
</plain>
<instances>
<instance part="B1" gate="G$1" x="22.86" y="142.24" smashed="yes" grouprefs="HALL_SENSOR1">
<attribute name="NAME" x="30.48" y="142.24" size="1.778" layer="94"/>
<attribute name="VALUE" x="30.48" y="139.7" size="1.778" layer="94"/>
</instance>
<instance part="GND10" gate="1" x="22.86" y="121.92" smashed="yes" grouprefs="HALL_SENSOR1">
<attribute name="VALUE" x="20.32" y="119.38" size="1.778" layer="96"/>
</instance>
<instance part="R13" gate="G$1" x="7.62" y="152.4" smashed="yes" rot="R90" grouprefs="HALL_SENSOR1">
<attribute name="NAME" x="5.08" y="146.05" size="1.778" layer="94" rot="R90"/>
<attribute name="VALUE" x="11.43" y="146.05" size="1.778" layer="94" rot="R90"/>
</instance>
<instance part="GND3" gate="1" x="27.94" y="205.74" smashed="yes" grouprefs="SERVO_CONTROL1">
<attribute name="VALUE" x="25.4" y="203.2" size="1.778" layer="96"/>
</instance>
<instance part="SW1" gate="G$1" x="15.24" y="203.2" smashed="yes" rot="R90" grouprefs="SERVO_CONTROL1">
<attribute name="NAME" x="10.16" y="198.12" size="1.778" layer="94" rot="R90"/>
<attribute name="VALUE" x="20.32" y="198.12" size="1.778" layer="94" rot="R90"/>
</instance>
<instance part="GND4" gate="1" x="15.24" y="187.96" smashed="yes" grouprefs="SERVO_CONTROL1">
<attribute name="VALUE" x="12.7" y="185.42" size="1.778" layer="96"/>
</instance>
<instance part="U4" gate="G$1" x="40.64" y="215.9" smashed="yes" grouprefs="SERVO_CONTROL1">
<attribute name="NAME" x="35.56" y="228.6" size="1.778" layer="94"/>
<attribute name="VALUE" x="35.56" y="203.2" size="1.778" layer="94"/>
</instance>
<instance part="GND20" gate="1" x="2.54" y="218.44" smashed="yes" grouprefs="SERVO_CONTROL1">
<attribute name="VALUE" x="0" y="215.9" size="1.778" layer="96"/>
</instance>
<instance part="R12" gate="G$1" x="2.54" y="200.66" smashed="yes" rot="R90" grouprefs="SERVO_CONTROL1">
<attribute name="NAME" x="0" y="194.31" size="1.778" layer="94" rot="R90"/>
<attribute name="VALUE" x="6.35" y="194.31" size="1.778" layer="94" rot="R90"/>
</instance>
<instance part="D1" gate="G$1" x="-124.46" y="121.92" smashed="yes" rot="R270" grouprefs="LED_CONTROL_GROUP1">
<attribute name="NAME" x="-129.54" y="129.54" size="1.778" layer="94" rot="R270"/>
<attribute name="VALUE" x="-132.08" y="129.54" size="1.778" layer="94" rot="R270"/>
</instance>
<instance part="Q1" gate="G$1" x="-124.46" y="106.68" smashed="yes" grouprefs="LED_CONTROL_GROUP1">
<attribute name="NAME" x="-120.65" y="107.95" size="1.778" layer="94"/>
<attribute name="VALUE" x="-120.65" y="104.14" size="1.778" layer="94"/>
</instance>
<instance part="R2" gate="G$1" x="-132.08" y="134.62" smashed="yes" rot="R180" grouprefs="LED_CONTROL_GROUP1">
<attribute name="NAME" x="-125.73" y="132.08" size="1.778" layer="94" rot="R180"/>
<attribute name="VALUE" x="-125.73" y="138.43" size="1.778" layer="94" rot="R180"/>
</instance>
<instance part="GND7" gate="1" x="-124.46" y="93.98" smashed="yes" grouprefs="LED_CONTROL_GROUP1">
<attribute name="VALUE" x="-127" y="91.44" size="1.778" layer="96"/>
</instance>
<instance part="R1" gate="G$1" x="-144.78" y="106.68" smashed="yes" grouprefs="LED_CONTROL_GROUP1">
<attribute name="NAME" x="-151.13" y="109.22" size="1.778" layer="94"/>
<attribute name="VALUE" x="-151.13" y="102.87" size="1.778" layer="94"/>
</instance>
<instance part="SB1" gate="G$1" x="50.8" y="81.28" smashed="yes" grouprefs="OPEN-CLOSE1">
<attribute name="NAME" x="45.72" y="78.74" size="1.778" layer="94"/>
<attribute name="VALUE" x="45.72" y="76.2" size="1.778" layer="94"/>
</instance>
<instance part="SB2" gate="G$1" x="50.8" y="60.96" smashed="yes" grouprefs="OPEN-CLOSE1">
<attribute name="NAME" x="45.72" y="58.42" size="1.778" layer="94"/>
<attribute name="VALUE" x="45.72" y="55.88" size="1.778" layer="94"/>
</instance>
<instance part="GND9" gate="1" x="68.58" y="58.42" smashed="yes" grouprefs="OPEN-CLOSE1">
<attribute name="VALUE" x="66.04" y="55.88" size="1.778" layer="96"/>
</instance>
<instance part="U1" gate="G$1" x="-147.32" y="208.28" smashed="yes" grouprefs="ESP1">
<attribute name="NAME" x="-152.4" y="236.22" size="1.778" layer="94"/>
<attribute name="VALUE" x="-152.4" y="180.34" size="1.778" layer="94"/>
</instance>
<instance part="GND2" gate="1" x="-83.82" y="226.06" smashed="yes" grouprefs="ESP1">
<attribute name="VALUE" x="-86.36" y="223.52" size="1.778" layer="96"/>
</instance>
<instance part="R4" gate="G$1" x="-115.57" y="203.2" smashed="yes" grouprefs="ESP1">
<attribute name="NAME" x="-121.92" y="205.74" size="1.778" layer="94"/>
<attribute name="VALUE" x="-121.92" y="199.39" size="1.778" layer="94"/>
</instance>
<instance part="R5" gate="G$1" x="-109.22" y="213.36" smashed="yes" grouprefs="ESP1">
<attribute name="NAME" x="-115.57" y="215.9" size="1.778" layer="94"/>
<attribute name="VALUE" x="-115.57" y="209.55" size="1.778" layer="94"/>
</instance>
<instance part="R7" gate="G$1" x="-96.52" y="218.44" smashed="yes" grouprefs="ESP1">
<attribute name="NAME" x="-102.87" y="220.98" size="1.778" layer="94"/>
<attribute name="VALUE" x="-102.87" y="214.63" size="1.778" layer="94"/>
</instance>
<instance part="R8" gate="G$1" x="-96.52" y="208.28" smashed="yes" grouprefs="ESP1">
<attribute name="NAME" x="-102.87" y="210.82" size="1.778" layer="94"/>
<attribute name="VALUE" x="-102.87" y="204.47" size="1.778" layer="94"/>
</instance>
<instance part="R6" gate="G$1" x="-104.14" y="187.96" smashed="yes" rot="R90" grouprefs="ESP1">
<attribute name="NAME" x="-100.33" y="183.515" size="1.778" layer="94" rot="R90"/>
<attribute name="VALUE" x="-97.79" y="182.88" size="1.778" layer="94" rot="R90"/>
</instance>
<instance part="GND8" gate="1" x="-104.14" y="177.8" smashed="yes" grouprefs="ESP1">
<attribute name="VALUE" x="-106.68" y="175.26" size="1.778" layer="96"/>
</instance>
<instance part="J1" gate="G$1" x="-83.82" y="58.42" smashed="yes" rot="R180" grouprefs="INPUT_CONNECTORS">
<attribute name="NAME" x="-96.52" y="55.88" size="1.778" layer="94" rot="R180"/>
<attribute name="NAME" x="-96.52" y="55.88" size="1.778" layer="94" rot="R180"/>
<attribute name="VALUE" x="-96.52" y="60.96" size="1.778" layer="94" rot="R180"/>
</instance>
<instance part="GND5" gate="1" x="-55.88" y="48.26" smashed="yes" grouprefs="INPUT_CONNECTORS">
<attribute name="VALUE" x="-58.42" y="45.72" size="1.778" layer="96"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="+5V" class="0">
<segment>
<wire x1="50.8" y1="223.52" x2="68.58" y2="223.52" width="0.1524" layer="91" grouprefs="SERVO_CONTROL1"/>
<label x="63.5" y="223.52" size="1.778" layer="95" grouprefs="SERVO_CONTROL1"/>
<pinref part="U4" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="B1" gate="G$1" pin="VCC"/>
<wire x1="22.86" y1="162.56" x2="22.86" y2="149.86" width="0.1524" layer="91" grouprefs="HALL_SENSOR1"/>
<wire x1="22.86" y1="162.56" x2="38.1" y2="162.56" width="0.1524" layer="91" grouprefs="HALL_SENSOR1"/>
<label x="33.02" y="160.02" size="1.778" layer="95" grouprefs="HALL_SENSOR1"/>
</segment>
<segment>
<pinref part="R2" gate="G$1" pin="P$2"/>
<wire x1="-140.97" y1="134.62" x2="-165.1" y2="134.62" width="0.1524" layer="91" grouprefs="LED_CONTROL_GROUP1"/>
<label x="-165.1" y="137.16" size="1.778" layer="95" grouprefs="LED_CONTROL_GROUP1"/>
</segment>
<segment>
<pinref part="U1" gate="G$1" pin="5V"/>
<wire x1="-167.64" y1="185.42" x2="-193.04" y2="185.42" width="0.1524" layer="91" grouprefs="ESP1"/>
<label x="-193.04" y="185.42" size="1.778" layer="95" grouprefs="ESP1"/>
</segment>
<segment>
<pinref part="J1" gate="G$1" pin="PIN2"/>
<wire x1="-78.74" y1="55.88" x2="-55.88" y2="55.88" width="0.1524" layer="91" grouprefs="INPUT_CONNECTORS"/>
<label x="-60.96" y="55.88" size="1.778" layer="95" grouprefs="INPUT_CONNECTORS"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="B1" gate="G$1" pin="GND"/>
<pinref part="GND10" gate="1" pin="GND"/>
<wire x1="22.86" y1="134.62" x2="22.86" y2="124.46" width="0.1524" layer="91" grouprefs="HALL_SENSOR1"/>
</segment>
<segment>
<pinref part="GND3" gate="1" pin="GND"/>
<wire x1="30.48" y1="208.28" x2="27.94" y2="208.28" width="0.1524" layer="91" grouprefs="SERVO_CONTROL1"/>
<pinref part="U4" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="GND4" gate="1" pin="GND"/>
<pinref part="SW1" gate="G$1" pin="P$1"/>
<wire x1="15.24" y1="190.5" x2="15.24" y2="193.04" width="0.1524" layer="91" grouprefs="SERVO_CONTROL1"/>
</segment>
<segment>
<pinref part="GND20" gate="1" pin="GND"/>
<pinref part="U4" gate="G$1" pin="1B"/>
<wire x1="2.54" y1="220.98" x2="30.48" y2="220.98" width="0.1524" layer="91" grouprefs="SERVO_CONTROL1"/>
</segment>
<segment>
<pinref part="GND7" gate="1" pin="GND"/>
<pinref part="Q1" gate="G$1" pin="E"/>
<wire x1="-124.46" y1="96.52" x2="-124.46" y2="99.06" width="0.1524" layer="91" grouprefs="LED_CONTROL_GROUP1"/>
</segment>
<segment>
<pinref part="SB2" gate="G$1" pin="P$2"/>
<pinref part="SB1" gate="G$1" pin="P$2"/>
<wire x1="60.96" y1="81.28" x2="60.96" y2="60.96" width="0.1524" layer="91" grouprefs="OPEN-CLOSE1"/>
<junction x="60.96" y="60.96" grouprefs="OPEN-CLOSE1"/>
<pinref part="GND9" gate="1" pin="GND"/>
<wire x1="60.96" y1="60.96" x2="68.58" y2="60.96" width="0.1524" layer="91" grouprefs="OPEN-CLOSE1"/>
</segment>
<segment>
<pinref part="U1" gate="G$1" pin="GND"/>
<wire x1="-127" y1="231.14" x2="-83.82" y2="231.14" width="0.1524" layer="91" grouprefs="ESP1"/>
<wire x1="-83.82" y1="231.14" x2="-83.82" y2="228.6" width="0.1524" layer="91" grouprefs="ESP1"/>
<pinref part="GND2" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="R6" gate="G$1" pin="P1"/>
<pinref part="GND8" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="J1" gate="G$1" pin="PIN1"/>
<wire x1="-78.74" y1="50.8" x2="-55.88" y2="50.8" width="0.1524" layer="91" grouprefs="INPUT_CONNECTORS"/>
<pinref part="GND5" gate="1" pin="GND"/>
</segment>
</net>
<net name="GPIO_TS_WINDOW_OPEN" class="0">
<segment>
<wire x1="40.64" y1="81.28" x2="5.08" y2="81.28" width="0.1524" layer="91" grouprefs="OPEN-CLOSE1"/>
<label x="5.08" y="81.28" size="1.778" layer="95" grouprefs="OPEN-CLOSE1"/>
<pinref part="SB1" gate="G$1" pin="P$1"/>
</segment>
<segment>
<pinref part="U1" gate="G$1" pin="IO4"/>
<wire x1="-127" y1="200.66" x2="-124.46" y2="200.66" width="0.1524" layer="91"/>
<wire x1="-124.46" y1="200.66" x2="-124.46" y2="198.12" width="0.1524" layer="91"/>
<wire x1="-124.46" y1="198.12" x2="-78.74" y2="198.12" width="0.1524" layer="91"/>
<label x="-111.76" y="198.12" size="1.778" layer="95"/>
</segment>
</net>
<net name="GPIO_TS_WINDOW_CLOSE" class="0">
<segment>
<wire x1="40.64" y1="60.96" x2="5.08" y2="60.96" width="0.1524" layer="91" grouprefs="OPEN-CLOSE1"/>
<label x="5.08" y="60.96" size="1.778" layer="95" grouprefs="OPEN-CLOSE1"/>
<pinref part="SB2" gate="G$1" pin="P$1"/>
</segment>
<segment>
<pinref part="U1" gate="G$1" pin="IO15"/>
<wire x1="-127" y1="193.04" x2="-119.38" y2="193.04" width="0.1524" layer="91" grouprefs="ESP1"/>
<wire x1="-119.38" y1="193.04" x2="-119.38" y2="167.64" width="0.1524" layer="91" grouprefs="ESP1"/>
<wire x1="-119.38" y1="167.64" x2="-68.58" y2="167.64" width="0.1524" layer="91" grouprefs="ESP1"/>
<label x="-99.06" y="170.18" size="1.778" layer="95" grouprefs="ESP1"/>
</segment>
</net>
<net name="HALL_OUT_INV" class="0">
<segment>
<pinref part="B1" gate="G$1" pin="OUT"/>
<pinref part="R13" gate="G$1" pin="P$1"/>
<wire x1="7.62" y1="142.24" x2="15.24" y2="142.24" width="0.1524" layer="91" grouprefs="HALL_SENSOR1"/>
<wire x1="7.62" y1="144.78" x2="7.62" y2="142.24" width="0.1524" layer="91" grouprefs="HALL_SENSOR1"/>
<junction x="7.62" y="142.24" grouprefs="HALL_SENSOR1"/>
<wire x1="7.62" y1="142.24" x2="-15.24" y2="142.24" width="0.1524" layer="91" grouprefs="HALL_SENSOR1"/>
<label x="-15.24" y="144.78" size="1.778" layer="95" grouprefs="HALL_SENSOR1"/>
</segment>
<segment>
<label x="10.16" y="223.52" size="1.778" layer="95" grouprefs="SERVO_CONTROL1"/>
<pinref part="U4" gate="G$1" pin="1A"/>
<wire x1="30.48" y1="223.52" x2="15.24" y2="223.52" width="0.1524" layer="91" grouprefs="SERVO_CONTROL1"/>
</segment>
<segment>
<pinref part="R8" gate="G$1" pin="P$2"/>
<wire x1="-87.63" y1="208.28" x2="-71.12" y2="208.28" width="0.1524" layer="91" grouprefs="ESP1"/>
<label x="-86.36" y="208.28" size="1.778" layer="95" grouprefs="ESP1"/>
</segment>
</net>
<net name="SERVO_PWM" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="3B"/>
<wire x1="50.8" y1="210.82" x2="78.74" y2="210.82" width="0.1524" layer="91" grouprefs="SERVO_CONTROL1"/>
<label x="63.5" y="210.82" size="1.778" layer="95" grouprefs="SERVO_CONTROL1"/>
</segment>
<segment>
<pinref part="R5" gate="G$1" pin="P$2"/>
<wire x1="-100.33" y1="213.36" x2="-78.74" y2="213.36" width="0.1524" layer="91" grouprefs="ESP1"/>
<label x="-91.44" y="213.36" size="1.778" layer="95" grouprefs="ESP1"/>
</segment>
</net>
<net name="SERVO_ENABLE_INV" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="4A"/>
<wire x1="50.8" y1="220.98" x2="73.66" y2="220.98" width="0.1524" layer="91" grouprefs="SERVO_CONTROL1"/>
<label x="50.8" y="220.98" size="1.778" layer="95" grouprefs="SERVO_CONTROL1"/>
</segment>
<segment>
<pinref part="R7" gate="G$1" pin="P$2"/>
<wire x1="-87.63" y1="218.44" x2="-78.74" y2="218.44" width="0.1524" layer="91" grouprefs="ESP1"/>
<label x="-91.44" y="218.44" size="1.778" layer="95" grouprefs="ESP1"/>
</segment>
</net>
<net name="SERVO_PWM_CONTROL" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="3Y"/>
<wire x1="50.8" y1="208.28" x2="78.74" y2="208.28" width="0.1524" layer="91" grouprefs="SERVO_CONTROL1"/>
<label x="55.88" y="208.28" size="1.778" layer="95" grouprefs="SERVO_CONTROL1"/>
</segment>
<segment>
<pinref part="J1" gate="G$1" pin="PIN3"/>
<wire x1="-78.74" y1="60.96" x2="-55.88" y2="60.96" width="0.1524" layer="91" grouprefs="INPUT_CONNECTORS"/>
<label x="-76.2" y="60.96" size="1.778" layer="95" grouprefs="INPUT_CONNECTORS"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="2Y"/>
<wire x1="30.48" y1="210.82" x2="22.86" y2="210.82" width="0.1524" layer="91" grouprefs="SERVO_CONTROL1"/>
<wire x1="22.86" y1="210.82" x2="22.86" y2="200.66" width="0.1524" layer="91" grouprefs="SERVO_CONTROL1"/>
<wire x1="22.86" y1="200.66" x2="86.36" y2="200.66" width="0.1524" layer="91" grouprefs="SERVO_CONTROL1"/>
<pinref part="U4" gate="G$1" pin="4B"/>
<wire x1="86.36" y1="200.66" x2="86.36" y2="218.44" width="0.1524" layer="91" grouprefs="SERVO_CONTROL1"/>
<wire x1="86.36" y1="218.44" x2="50.8" y2="218.44" width="0.1524" layer="91" grouprefs="SERVO_CONTROL1"/>
</segment>
</net>
<net name="SW_IS_ON_INV" class="0">
<segment>
<pinref part="SW1" gate="G$1" pin="P$2"/>
<pinref part="U4" gate="G$1" pin="2B"/>
<wire x1="15.24" y1="213.36" x2="30.48" y2="213.36" width="0.1524" layer="91" grouprefs="SERVO_CONTROL1"/>
<pinref part="R12" gate="G$1" pin="P$2"/>
<wire x1="2.54" y1="209.55" x2="2.54" y2="213.36" width="0.1524" layer="91" grouprefs="SERVO_CONTROL1"/>
<wire x1="2.54" y1="213.36" x2="15.24" y2="213.36" width="0.1524" layer="91" grouprefs="SERVO_CONTROL1"/>
<junction x="15.24" y="213.36" grouprefs="SERVO_CONTROL1"/>
<wire x1="2.54" y1="213.36" x2="-10.16" y2="213.36" width="0.1524" layer="91" grouprefs="SERVO_CONTROL1"/>
<junction x="2.54" y="213.36" grouprefs="SERVO_CONTROL1"/>
<label x="-17.78" y="210.82" size="1.778" layer="95" grouprefs="SERVO_CONTROL1"/>
</segment>
<segment>
<pinref part="R4" gate="G$1" pin="P$2"/>
<wire x1="-106.68" y1="203.2" x2="-71.12" y2="203.2" width="0.1524" layer="91" grouprefs="ESP1"/>
<label x="-83.82" y="203.2" size="1.778" layer="95" grouprefs="ESP1"/>
</segment>
</net>
<net name="N$52" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="4Y"/>
<wire x1="50.8" y1="215.9" x2="55.88" y2="215.9" width="0.1524" layer="91" grouprefs="SERVO_CONTROL1"/>
<wire x1="55.88" y1="215.9" x2="55.88" y2="213.36" width="0.1524" layer="91" grouprefs="SERVO_CONTROL1"/>
<pinref part="U4" gate="G$1" pin="3A"/>
<wire x1="55.88" y1="213.36" x2="50.8" y2="213.36" width="0.1524" layer="91" grouprefs="SERVO_CONTROL1"/>
</segment>
</net>
<net name="3V3" class="0">
<segment>
<pinref part="R13" gate="G$1" pin="P$2"/>
<wire x1="7.62" y1="161.29" x2="-12.7" y2="161.29" width="0.1524" layer="91" grouprefs="HALL_SENSOR1"/>
<label x="-12.7" y="162.56" size="1.778" layer="95" grouprefs="HALL_SENSOR1"/>
</segment>
<segment>
<pinref part="R12" gate="G$1" pin="P$1"/>
<wire x1="2.54" y1="193.04" x2="2.54" y2="187.96" width="0.1524" layer="91" grouprefs="SERVO_CONTROL1"/>
<label x="0" y="185.42" size="1.778" layer="95" grouprefs="SERVO_CONTROL1"/>
</segment>
<segment>
<pinref part="U1" gate="G$1" pin="3V3"/>
<wire x1="-167.64" y1="231.14" x2="-193.04" y2="231.14" width="0.1524" layer="91" grouprefs="ESP1"/>
<label x="-193.04" y="231.14" size="1.778" layer="95" grouprefs="ESP1"/>
</segment>
</net>
<net name="N$56" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="2A"/>
<pinref part="U4" gate="G$1" pin="1Y"/>
<wire x1="30.48" y1="218.44" x2="22.86" y2="218.44" width="0.1524" layer="91" grouprefs="SERVO_CONTROL1"/>
<wire x1="22.86" y1="218.44" x2="22.86" y2="215.9" width="0.1524" layer="91" grouprefs="SERVO_CONTROL1"/>
<wire x1="22.86" y1="215.9" x2="30.48" y2="215.9" width="0.1524" layer="91" grouprefs="SERVO_CONTROL1"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="R1" gate="G$1" pin="P$2"/>
<pinref part="Q1" gate="G$1" pin="B"/>
<wire x1="-135.89" y1="106.68" x2="-132.08" y2="106.68" width="0.1524" layer="91" grouprefs="LED_CONTROL_GROUP1"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="Q1" gate="G$1" pin="C"/>
<pinref part="D1" gate="G$1" pin="PIN_ANODE"/>
<wire x1="-124.46" y1="114.3" x2="-124.46" y2="116.84" width="0.1524" layer="91" grouprefs="LED_CONTROL_GROUP1"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="D1" gate="G$1" pin="PIN_CATHODE"/>
<pinref part="R2" gate="G$1" pin="P$1"/>
<wire x1="-124.46" y1="129.54" x2="-124.46" y2="134.62" width="0.1524" layer="91" grouprefs="LED_CONTROL_GROUP1"/>
</segment>
</net>
<net name="LED_CONTROL" class="0">
<segment>
<pinref part="R1" gate="G$1" pin="P$1"/>
<wire x1="-152.4" y1="106.68" x2="-167.64" y2="106.68" width="0.1524" layer="91" grouprefs="LED_CONTROL_GROUP1"/>
<label x="-170.18" y="106.68" size="1.778" layer="95" grouprefs="LED_CONTROL_GROUP1"/>
</segment>
<segment>
<pinref part="U1" gate="G$1" pin="IO33"/>
<wire x1="-167.64" y1="213.36" x2="-193.04" y2="213.36" width="0.1524" layer="91" grouprefs="ESP1"/>
<label x="-193.04" y="213.36" size="1.778" layer="95" grouprefs="ESP1"/>
</segment>
</net>
<net name="OUTDOOR_SIGNAL" class="0">
<segment>
<label x="-101.6" y="193.04" size="1.778" layer="95" grouprefs="ESP1"/>
<pinref part="R6" gate="G$1" pin="P2"/>
<wire x1="-104.14" y1="195.58" x2="-73.66" y2="195.58" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="J1" gate="G$1" pin="PIN4"/>
<wire x1="-78.74" y1="66.04" x2="-55.88" y2="66.04" width="0.1524" layer="91" grouprefs="INPUT_CONNECTORS"/>
<label x="-76.2" y="66.04" size="1.778" layer="95" grouprefs="INPUT_CONNECTORS"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="IO19"/>
<pinref part="R5" gate="G$1" pin="P$1"/>
<wire x1="-127" y1="213.36" x2="-116.84" y2="213.36" width="0.1524" layer="91" grouprefs="ESP1"/>
</segment>
</net>
<net name="N$28" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="IO21"/>
<pinref part="R7" gate="G$1" pin="P$1"/>
<wire x1="-127" y1="218.44" x2="-104.14" y2="218.44" width="0.1524" layer="91" grouprefs="ESP1"/>
</segment>
</net>
<net name="N$32" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="IO16"/>
<pinref part="R4" gate="G$1" pin="P$1"/>
<wire x1="-127" y1="203.2" x2="-123.19" y2="203.2" width="0.1524" layer="91" grouprefs="ESP1"/>
</segment>
</net>
<net name="N$29" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="IO18"/>
<wire x1="-127" y1="210.82" x2="-116.84" y2="210.82" width="0.1524" layer="91" grouprefs="ESP1"/>
<pinref part="R8" gate="G$1" pin="P$1"/>
<wire x1="-116.84" y1="210.82" x2="-116.84" y2="208.28" width="0.1524" layer="91" grouprefs="ESP1"/>
<wire x1="-116.84" y1="208.28" x2="-104.14" y2="208.28" width="0.1524" layer="91" grouprefs="ESP1"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="IO2"/>
<wire x1="-127" y1="195.58" x2="-111.76" y2="195.58" width="0.1524" layer="91" grouprefs="ESP1"/>
<pinref part="R6" gate="G$1" pin="P3"/>
<wire x1="-111.76" y1="195.58" x2="-111.76" y2="187.96" width="0.1524" layer="91" grouprefs="ESP1"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
<errors>
<approved hash="102,1,22.86,149.86,VCC,+5V,,,,"/>
<approved hash="102,1,-167.64,185.42,5V,+5V,,,,"/>
<approved hash="104,1,50.8,223.52,U4,VCC,+5V,,,"/>
</errors>
</schematic>
</drawing>
<compatibility>
<note version="8.2" severity="warning">
Since Version 8.2, EAGLE supports online libraries. The ids
of those online libraries will not be understood (or retained)
with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports URNs for individual library
assets (packages, symbols, and devices). The URNs of those assets
will not be understood (or retained) with this version.
</note>
<note version="9.5" severity="warning">
Since Version 9.5, EAGLE supports persistent groups with
schematics, and board files. Those persistent groups
will not be understood (or retained) with this version.
</note>
</compatibility>
</eagle>
