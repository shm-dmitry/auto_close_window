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
<layer number="2" name="Route2" color="16" fill="1" visible="no" active="no"/>
<layer number="3" name="Route3" color="17" fill="1" visible="no" active="no"/>
<layer number="4" name="Route4" color="18" fill="1" visible="no" active="no"/>
<layer number="5" name="Route5" color="19" fill="1" visible="no" active="no"/>
<layer number="6" name="Route6" color="25" fill="1" visible="no" active="no"/>
<layer number="7" name="Route7" color="26" fill="1" visible="no" active="no"/>
<layer number="8" name="Route8" color="27" fill="1" visible="no" active="no"/>
<layer number="9" name="Route9" color="28" fill="1" visible="no" active="no"/>
<layer number="10" name="Route10" color="29" fill="1" visible="no" active="no"/>
<layer number="11" name="Route11" color="30" fill="1" visible="no" active="no"/>
<layer number="12" name="Route12" color="20" fill="1" visible="no" active="no"/>
<layer number="13" name="Route13" color="21" fill="1" visible="no" active="no"/>
<layer number="14" name="Route14" color="22" fill="1" visible="no" active="no"/>
<layer number="15" name="Route15" color="23" fill="1" visible="no" active="no"/>
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
<package name="C">
<pad name="PIN_PLUS" x="-2.54" y="0" drill="0.8" shape="square"/>
<pad name="PIN_GND" x="2.54" y="0" drill="0.8" shape="square"/>
<circle x="0" y="0" radius="5.08" width="0.127" layer="21"/>
<wire x1="-3.175" y1="-1.905" x2="-1.905" y2="-1.905" width="0.127" layer="21"/>
<wire x1="-2.54" y1="-1.27" x2="-2.54" y2="-2.54" width="0.127" layer="21"/>
<wire x1="1.905" y1="-1.905" x2="3.175" y2="-1.905" width="0.127" layer="21"/>
<text x="-2.54" y="2.54" size="1.27" layer="21">&gt;NAME</text>
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
<text x="-2.54" y="2.54" size="1.27" layer="21">&gt;NAME</text>
</package>
<package name="MOSFET_N">
<pad name="S" x="2.54" y="0" drill="1" shape="square"/>
<pad name="D" x="0" y="0" drill="1" shape="square"/>
<pad name="G" x="-2.54" y="0" drill="1" shape="square"/>
<text x="-4.064" y="-0.635" size="0.6096" layer="21">G</text>
<text x="-1.524" y="-0.635" size="0.6096" layer="21">D</text>
<text x="1.27" y="-0.635" size="0.6096" layer="21">S</text>
<wire x1="-5.08" y1="2.54" x2="-5.08" y2="1.27" width="0.127" layer="21"/>
<wire x1="5.08" y1="-1.27" x2="5.08" y2="0" width="0.127" layer="21"/>
<wire x1="5.08" y1="0" x2="5.08" y2="1.27" width="0.127" layer="21"/>
<wire x1="5.08" y1="1.27" x2="5.08" y2="2.54" width="0.127" layer="21"/>
<wire x1="5.08" y1="2.54" x2="1.27" y2="2.54" width="0.127" layer="21"/>
<wire x1="1.27" y1="2.54" x2="-1.27" y2="2.54" width="0.127" layer="21"/>
<wire x1="-1.27" y1="2.54" x2="-5.08" y2="2.54" width="0.127" layer="21"/>
<wire x1="-5.08" y1="1.27" x2="-1.27" y2="1.27" width="0.127" layer="21"/>
<wire x1="-1.27" y1="1.27" x2="1.27" y2="1.27" width="0.127" layer="21"/>
<wire x1="1.27" y1="1.27" x2="5.08" y2="1.27" width="0.127" layer="21"/>
<wire x1="-1.27" y1="2.54" x2="-1.27" y2="1.27" width="0.127" layer="21"/>
<wire x1="1.27" y1="2.54" x2="1.27" y2="1.27" width="0.127" layer="21"/>
<wire x1="-5.08" y1="1.27" x2="-5.08" y2="-2.54" width="0.127" layer="21"/>
<wire x1="-5.08" y1="-2.54" x2="5.08" y2="-2.54" width="0.127" layer="21"/>
<wire x1="5.08" y1="-2.54" x2="5.08" y2="-1.27" width="0.127" layer="21"/>
<text x="-2.54" y="3.81" size="1.27" layer="21">&gt;NAME</text>
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
<package name="D_SCHOTTKY">
<pad name="ANODE" x="-3.81" y="0" drill="0.7" shape="square"/>
<pad name="CATHODE" x="3.81" y="0" drill="0.7" shape="square"/>
<wire x1="-5.08" y1="1.905" x2="-5.08" y2="-1.905" width="0.127" layer="21"/>
<wire x1="-5.08" y1="-1.905" x2="5.08" y2="-1.905" width="0.127" layer="21"/>
<wire x1="5.08" y1="-1.905" x2="5.08" y2="1.905" width="0.127" layer="21"/>
<wire x1="5.08" y1="1.905" x2="-5.08" y2="1.905" width="0.127" layer="21"/>
<wire x1="-1.27" y1="0" x2="-1.27" y2="1.27" width="0.127" layer="21"/>
<wire x1="-1.27" y1="1.27" x2="1.27" y2="0" width="0.127" layer="21"/>
<wire x1="1.27" y1="0" x2="-1.27" y2="-1.27" width="0.127" layer="21"/>
<wire x1="-1.27" y1="-1.27" x2="-1.27" y2="0" width="0.127" layer="21"/>
<wire x1="1.27" y1="1.27" x2="1.27" y2="0" width="0.127" layer="21"/>
<wire x1="1.27" y1="0" x2="1.27" y2="-1.27" width="0.127" layer="21"/>
<wire x1="1.27" y1="-1.27" x2="0.635" y2="-1.27" width="0.127" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="0.635" y2="-0.635" width="0.127" layer="21"/>
<text x="-2.54" y="2.54" size="1.27" layer="21">&gt;NAME</text>
<wire x1="-3.81" y1="0" x2="-1.27" y2="0" width="0.127" layer="21"/>
<wire x1="1.27" y1="0" x2="3.81" y2="0" width="0.127" layer="21"/>
</package>
<package name="L-RLB0914">
<pad name="P$1" x="2.54" y="0" drill="0.8" shape="square"/>
<pad name="P$2" x="-2.54" y="0" drill="0.8" shape="square"/>
<circle x="0" y="0" radius="5.08" width="0.127" layer="21"/>
<text x="-2.54" y="2.54" size="1.27" layer="21">&gt;NAME</text>
</package>
<package name="SERVO">
<pad name="VCC" x="0" y="0" drill="1" shape="square"/>
<pad name="PULSE" x="0" y="2.54" drill="1" shape="square"/>
<pad name="GND" x="0" y="-2.54" drill="1" shape="square"/>
<wire x1="-2.54" y1="5.08" x2="-2.54" y2="-5.08" width="0.127" layer="21"/>
<wire x1="-2.54" y1="-5.08" x2="2.54" y2="-5.08" width="0.127" layer="21"/>
<wire x1="2.54" y1="-5.08" x2="2.54" y2="5.08" width="0.127" layer="21"/>
<wire x1="2.54" y1="5.08" x2="-2.54" y2="5.08" width="0.127" layer="21"/>
<text x="-0.635" y="3.4925" size="0.6096" layer="21">PULSE</text>
<text x="-0.635" y="0.9525" size="0.6096" layer="21">VCC</text>
<text x="-0.635" y="-1.5875" size="0.6096" layer="21">GND</text>
<text x="-2.54" y="6.35" size="1.27" layer="21">&gt;NAME</text>
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
<text x="-2.54" y="6.35" size="1.27" layer="21">&gt;NAME</text>
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
<package name="L-EC24">
<pad name="P$1" x="-7.62" y="0" drill="0.8" shape="square"/>
<pad name="P$2" x="7.62" y="0" drill="0.8" shape="square"/>
<wire x1="-7.62" y1="0" x2="-5.08" y2="0" width="0.127" layer="21"/>
<wire x1="7.62" y1="0" x2="5.08" y2="0" width="0.127" layer="21"/>
<wire x1="-5.08" y1="0" x2="-2.54" y2="0" width="0.127" layer="21" curve="-180"/>
<wire x1="-2.54" y1="0" x2="0" y2="0" width="0.127" layer="21" curve="-180"/>
<wire x1="0" y1="0" x2="2.54" y2="0" width="0.127" layer="21" curve="-180"/>
<wire x1="2.54" y1="0" x2="5.08" y2="0" width="0.127" layer="21" curve="-180"/>
<text x="-3.81" y="2.54" size="1.27" layer="21">&gt;NAME</text>
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
<package name="SB-NC">
<pad name="P$1" x="-3.81" y="0" drill="0.8" shape="square"/>
<pad name="P$2" x="3.81" y="0" drill="0.8" shape="square"/>
<wire x1="-5.715" y1="-2.54" x2="-5.715" y2="2.54" width="0.127" layer="21"/>
<wire x1="5.715" y1="2.54" x2="5.715" y2="-2.54" width="0.127" layer="21"/>
<wire x1="5.715" y1="-2.54" x2="-5.715" y2="-2.54" width="0.127" layer="21"/>
<wire x1="5.715" y1="2.54" x2="-5.715" y2="2.54" width="0.127" layer="21"/>
<text x="-2.54" y="1.27" size="1.27" layer="21">&gt;NAME</text>
</package>
<package name="JST-XH254-3P">
<pad name="PIN2" x="0" y="0" drill="0.8" shape="square"/>
<pad name="PIN1" x="-2.54" y="0" drill="0.8" shape="square"/>
<pad name="PIN3" x="2.54" y="0" drill="0.8" shape="square"/>
<wire x1="-5.08" y1="2.54" x2="-5.08" y2="-2.54" width="0.127" layer="21"/>
<wire x1="-5.08" y1="-2.54" x2="5.08" y2="-2.54" width="0.127" layer="21"/>
<wire x1="5.08" y1="-2.54" x2="5.08" y2="2.54" width="0.127" layer="21"/>
<wire x1="5.08" y1="2.54" x2="-5.08" y2="2.54" width="0.127" layer="21"/>
<text x="-2.54" y="-3.81" size="1.27" layer="21">&gt;NAME</text>
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
<package name="JST-XH254-2P">
<pad name="PIN1" x="-1.27" y="0" drill="0.8" shape="square"/>
<pad name="PIN2" x="1.27" y="0" drill="0.8" shape="square"/>
<wire x1="-3.81" y1="2.54" x2="-3.81" y2="-2.54" width="0.127" layer="21"/>
<wire x1="-3.81" y1="-2.54" x2="3.81" y2="-2.54" width="0.127" layer="21"/>
<wire x1="3.81" y1="-2.54" x2="3.81" y2="2.54" width="0.127" layer="21"/>
<wire x1="3.81" y1="2.54" x2="-3.81" y2="2.54" width="0.127" layer="21"/>
<text x="-3.81" y="-3.81" size="1.27" layer="21">&gt;NAME</text>
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
<symbol name="MOSFET_N">
<wire x1="1.27" y1="2.54" x2="1.27" y2="-2.54" width="0.254" layer="94"/>
<wire x1="0.635" y1="2.54" x2="0.635" y2="1.905" width="0.254" layer="94"/>
<wire x1="0.635" y1="1.905" x2="0.635" y2="1.27" width="0.254" layer="94"/>
<wire x1="0.635" y1="0.635" x2="0.635" y2="0" width="0.254" layer="94"/>
<wire x1="0.635" y1="0" x2="0.635" y2="-0.635" width="0.254" layer="94"/>
<wire x1="0.635" y1="-1.27" x2="0.635" y2="-1.905" width="0.254" layer="94"/>
<pin name="G" x="6.35" y="-2.54" visible="off" length="middle" rot="R180"/>
<circle x="-0.635" y="0" radius="5.11953125" width="0.254" layer="94"/>
<wire x1="0.635" y1="-1.905" x2="0.635" y2="-2.54" width="0.254" layer="94"/>
<pin name="D" x="-2.54" y="6.985" visible="off" length="middle" rot="R270"/>
<pin name="S" x="-2.54" y="-6.985" visible="off" length="middle" rot="R90"/>
<wire x1="-2.54" y1="-1.905" x2="0.635" y2="-1.905" width="0.254" layer="94"/>
<wire x1="-2.54" y1="0" x2="0.635" y2="0" width="0.254" layer="94"/>
<polygon width="0.254" layer="94">
<vertex x="0.635" y="0"/>
<vertex x="-0.635" y="0.635"/>
<vertex x="-0.635" y="-0.635"/>
</polygon>
<wire x1="-4.445" y1="1.27" x2="-3.81" y2="1.27" width="0.254" layer="94"/>
<polygon width="0.254" layer="94">
<vertex x="-3.81" y="1.27"/>
<vertex x="-4.445" y="-0.635"/>
<vertex x="-3.175" y="-0.635"/>
</polygon>
<wire x1="-3.81" y1="1.27" x2="-3.175" y2="1.27" width="0.254" layer="94"/>
<wire x1="-3.81" y1="1.27" x2="-3.81" y2="3.175" width="0.254" layer="94"/>
<wire x1="-3.81" y1="-0.635" x2="-3.81" y2="-3.175" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-1.905" x2="-2.54" y2="0" width="0.254" layer="94"/>
<wire x1="-2.54" y1="1.905" x2="0.635" y2="1.905" width="0.254" layer="94"/>
<wire x1="-3.81" y1="-3.175" x2="-2.54" y2="-3.175" width="0.254" layer="94"/>
<wire x1="-3.81" y1="3.175" x2="-2.54" y2="3.175" width="0.254" layer="94"/>
<text x="-16.51" y="2.54" size="1.778" layer="94">&gt;NAME</text>
<text x="-16.51" y="-5.08" size="1.778" layer="94">&gt;VALUE</text>
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
<symbol name="TRANSISTOR_PNP">
<pin name="B" x="-7.62" y="0" visible="off" length="middle"/>
<pin name="C" x="0" y="7.62" visible="off" length="middle" rot="R270"/>
<pin name="E" x="0" y="-7.62" visible="off" length="middle" rot="R90"/>
<circle x="0" y="0" radius="3.81" width="0.254" layer="94"/>
<wire x1="-2.54" y1="2.54" x2="-2.54" y2="0" width="0.254" layer="94"/>
<wire x1="-2.54" y1="0" x2="-2.54" y2="-2.54" width="0.254" layer="94"/>
<wire x1="0" y1="2.54" x2="-2.54" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="-2.54" x2="-2.54" y2="0" width="0.254" layer="94"/>
<text x="3.81" y="1.27" size="1.778" layer="94">&gt;NAME</text>
<text x="3.81" y="-2.54" size="1.778" layer="94">&gt;VALUE</text>
<polygon width="0.254" layer="94">
<vertex x="-2.032" y="-0.508"/>
<vertex x="-1.016" y="-0.508"/>
<vertex x="-2.032" y="-1.524"/>
</polygon>
</symbol>
<symbol name="D_SCHOTTKY">
<pin name="ANODE" x="-7.62" y="0" visible="off" length="middle"/>
<pin name="CATHODE" x="5.08" y="0" visible="off" length="middle" rot="R180"/>
<wire x1="-2.54" y1="1.27" x2="-2.54" y2="-1.27" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-1.27" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="-2.54" y1="1.27" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="1.27" x2="0" y2="-1.27" width="0.254" layer="94"/>
<wire x1="0" y1="-1.27" x2="-0.635" y2="-1.27" width="0.254" layer="94"/>
<wire x1="0" y1="1.27" x2="0.635" y2="1.27" width="0.254" layer="94"/>
<wire x1="0.635" y1="1.27" x2="0.635" y2="0.635" width="0.254" layer="94"/>
<wire x1="-0.635" y1="-0.635" x2="-0.635" y2="-1.27" width="0.254" layer="94"/>
<text x="-5.715" y="2.54" size="1.778" layer="94">&gt;NAME</text>
<text x="-5.715" y="-3.81" size="1.778" layer="94">&gt;VALUE</text>
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
<symbol name="SERVO">
<wire x1="-5.08" y1="7.62" x2="-5.08" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-7.62" x2="8.89" y2="-7.62" width="0.254" layer="94"/>
<wire x1="8.89" y1="-7.62" x2="8.89" y2="7.62" width="0.254" layer="94"/>
<wire x1="8.89" y1="7.62" x2="-5.08" y2="7.62" width="0.254" layer="94"/>
<circle x="5.715" y="0.635" radius="2.54" width="0.254" layer="94"/>
<wire x1="5.715" y1="3.175" x2="15.24" y2="6.35" width="0.254" layer="94"/>
<wire x1="15.24" y1="6.35" x2="16.51" y2="4.445" width="0.254" layer="94" curve="-137.726311"/>
<wire x1="7.62" y1="-1.27" x2="16.51" y2="4.445" width="0.254" layer="94"/>
<pin name="PULSE" x="-10.16" y="5.08" length="middle" direction="in"/>
<pin name="VCC" x="-10.16" y="0" length="middle" direction="pwr"/>
<pin name="GND" x="-10.16" y="-5.08" length="middle" direction="pwr"/>
<text x="-2.54" y="-10.16" size="1.778" layer="94">&gt;VALUE</text>
<text x="-2.54" y="10.16" size="1.778" layer="94">&gt;NAME</text>
</symbol>
<symbol name="NE555P">
<pin name="OUT" x="-10.16" y="0" visible="off" length="middle" direction="out"/>
<pin name="TRIG" x="-10.16" y="2.54" visible="off" length="middle"/>
<pin name="RESET" x="-10.16" y="-2.54" visible="off" length="middle"/>
<pin name="GND" x="-10.16" y="5.08" visible="off" length="middle" direction="pwr"/>
<pin name="VCC" x="10.16" y="5.08" visible="off" length="middle" direction="pwr" rot="R180"/>
<pin name="DISCH" x="10.16" y="2.54" visible="off" length="middle" rot="R180"/>
<pin name="THRES" x="10.16" y="0" visible="off" length="middle" rot="R180"/>
<pin name="CONT" x="10.16" y="-2.54" visible="off" length="middle" rot="R180"/>
<wire x1="-5.08" y1="7.62" x2="-5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-5.08" x2="5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="-5.08" x2="5.08" y2="7.62" width="0.254" layer="94"/>
<wire x1="5.08" y1="7.62" x2="0.635" y2="7.62" width="0.254" layer="94"/>
<text x="-5.08" y="10.16" size="1.778" layer="94">&gt;NAME</text>
<text x="-5.08" y="-7.62" size="1.778" layer="94">&gt;VALUE</text>
<text x="-4.445" y="5.08" size="0.8128" layer="94">GND</text>
<text x="-4.445" y="2.54" size="0.8128" layer="94">TRIG</text>
<text x="-4.445" y="0" size="0.8128" layer="94">OUT</text>
<text x="-4.445" y="-2.54" size="0.8128" layer="94">RST</text>
<text x="1.905" y="5.08" size="0.8128" layer="94">VCC</text>
<text x="1.27" y="2.54" size="0.8128" layer="94">DISCH</text>
<text x="0.635" y="0" size="0.8128" layer="94">THRES</text>
<text x="1.27" y="-2.54" size="0.8128" layer="94">CONT</text>
<wire x1="0.635" y1="7.62" x2="-0.635" y2="7.62" width="0.254" layer="94"/>
<wire x1="-0.635" y1="7.62" x2="-5.08" y2="7.62" width="0.254" layer="94"/>
<wire x1="-0.635" y1="7.62" x2="-0.635" y2="6.985" width="0.254" layer="94"/>
<wire x1="-0.635" y1="6.985" x2="0.635" y2="6.985" width="0.254" layer="94"/>
<wire x1="0.635" y1="7.62" x2="0.635" y2="6.985" width="0.254" layer="94"/>
</symbol>
<symbol name="LM311P">
<wire x1="-5.08" y1="5.08" x2="-5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-5.08" x2="-0.3175" y2="-1.905" width="0.254" layer="94"/>
<wire x1="-0.3175" y1="-1.905" x2="2.54" y2="0" width="0.254" layer="94"/>
<wire x1="2.54" y1="0" x2="-5.08" y2="5.08" width="0.254" layer="94"/>
<pin name="IN+" x="-10.16" y="2.54" visible="off" length="middle" direction="in"/>
<pin name="IN-" x="-10.16" y="-2.54" visible="off" length="middle" direction="in"/>
<pin name="GND" x="-2.54" y="-10.16" visible="off" length="middle" direction="pwr" rot="R90"/>
<pin name="VCC" x="-2.54" y="10.16" visible="off" length="middle" direction="pwr" rot="R270"/>
<pin name="EMI_OUT" x="7.62" y="0" visible="off" length="middle" direction="out" rot="R180"/>
<pin name="BAL_STROBE" x="7.62" y="-5.08" visible="off" length="middle" direction="in" rot="R180"/>
<pin name="BALANCE" x="7.62" y="-7.62" visible="off" length="middle" direction="in" rot="R180"/>
<pin name="COL_OUT" x="7.62" y="5.08" visible="off" length="middle" direction="out" rot="R180"/>
<wire x1="-2.54" y1="-5.08" x2="-2.54" y2="-3.4925" width="0.254" layer="94"/>
<wire x1="-2.54" y1="5.08" x2="-2.54" y2="3.4925" width="0.254" layer="94"/>
<wire x1="2.54" y1="5.08" x2="2.54" y2="0" width="0.254" layer="94"/>
<wire x1="2.54" y1="-5.08" x2="-0.3175" y2="-5.08" width="0.254" layer="94"/>
<wire x1="-0.3175" y1="-5.08" x2="-0.3175" y2="-1.905" width="0.254" layer="94"/>
<wire x1="-0.3175" y1="-5.08" x2="-0.3175" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-0.3175" y1="-7.62" x2="2.54" y2="-7.62" width="0.254" layer="94"/>
<text x="-4.7625" y="5.715" size="0.6096" layer="94">VCC</text>
<text x="-4.7625" y="-6.0325" size="0.6096" layer="94">GND</text>
<text x="-4.445" y="1.905" size="1.27" layer="94">+</text>
<text x="-4.1275" y="-3.175" size="1.27" layer="94">-</text>
<text x="2.8575" y="0.3175" size="0.6096" layer="94">EMI_OUT</text>
<text x="2.8575" y="4.1275" size="0.6096" layer="94">COL_OUT</text>
<text x="1.27" y="-4.7625" size="0.6096" layer="94">BAL/STROBE</text>
<text x="2.54" y="-7.3025" size="0.6096" layer="94">BALANCE</text>
<text x="-15.24" y="-7.62" size="1.778" layer="94">&gt;NAME</text>
<text x="-15.24" y="-10.16" size="1.778" layer="94">&gt;VALUE</text>
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
<symbol name="SB-NC">
<pin name="P$1" x="-10.16" y="0" visible="off" length="middle"/>
<pin name="P$2" x="10.16" y="0" visible="off" length="middle" rot="R180"/>
<wire x1="-5.08" y1="0" x2="-2.54" y2="0" width="0.254" layer="94"/>
<wire x1="2.54" y1="0" x2="5.08" y2="0" width="0.254" layer="94"/>
<wire x1="2.54" y1="2.54" x2="2.54" y2="0" width="0.254" layer="94"/>
<wire x1="-2.54" y1="0" x2="3.81" y2="2.54" width="0.254" layer="94"/>
<wire x1="0" y1="1.27" x2="0" y2="3.81" width="0.254" layer="94" style="shortdash"/>
<wire x1="-1.27" y1="3.81" x2="-1.27" y2="2.54" width="0.254" layer="94"/>
<wire x1="-1.27" y1="3.81" x2="1.27" y2="3.81" width="0.254" layer="94"/>
<wire x1="1.27" y1="3.81" x2="1.27" y2="2.54" width="0.254" layer="94"/>
<text x="-5.08" y="-2.54" size="1.778" layer="94">&gt;NAME</text>
<text x="-5.08" y="-5.08" size="1.778" layer="94">&gt;VALUE</text>
</symbol>
<symbol name="JST-XH254-3P">
<pin name="PIN1" x="-5.08" y="5.08" length="middle"/>
<pin name="PIN2" x="-5.08" y="0" length="middle"/>
<pin name="PIN3" x="-5.08" y="-5.08" length="middle"/>
<wire x1="0" y1="7.62" x2="0" y2="-7.62" width="0.254" layer="94"/>
<wire x1="0" y1="-7.62" x2="10.16" y2="-7.62" width="0.254" layer="94"/>
<wire x1="10.16" y1="-7.62" x2="10.16" y2="7.62" width="0.254" layer="94"/>
<wire x1="10.16" y1="7.62" x2="0" y2="7.62" width="0.254" layer="94"/>
<text x="12.7" y="2.54" size="1.778" layer="94">&gt;NAME</text>
<text x="12.7" y="-2.54" size="1.778" layer="94">&gt;VALUE</text>
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
<symbol name="JST-XH254-2P">
<pin name="PIN1" x="-5.08" y="2.54" length="middle"/>
<pin name="PIN2" x="-5.08" y="-2.54" length="middle"/>
<wire x1="0" y1="5.08" x2="0" y2="-5.08" width="0.254" layer="94"/>
<wire x1="0" y1="-5.08" x2="10.16" y2="-5.08" width="0.254" layer="94"/>
<wire x1="10.16" y1="-5.08" x2="10.16" y2="5.08" width="0.254" layer="94"/>
<wire x1="10.16" y1="5.08" x2="0" y2="5.08" width="0.254" layer="94"/>
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
<deviceset name="MOSFET_N" prefix="Q">
<gates>
<gate name="G$1" symbol="MOSFET_N" x="-1.27" y="0"/>
</gates>
<devices>
<device name="" package="MOSFET_N">
<connects>
<connect gate="G$1" pin="D" pad="D"/>
<connect gate="G$1" pin="G" pad="G"/>
<connect gate="G$1" pin="S" pad="S"/>
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
<deviceset name="TRANSISTOR_PNP" prefix="Q" uservalue="yes">
<gates>
<gate name="G$1" symbol="TRANSISTOR_PNP" x="0" y="0"/>
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
<deviceset name="D_SCHOTTKY" prefix="D">
<gates>
<gate name="G$1" symbol="D_SCHOTTKY" x="0" y="0"/>
</gates>
<devices>
<device name="" package="D_SCHOTTKY">
<connects>
<connect gate="G$1" pin="ANODE" pad="ANODE"/>
<connect gate="G$1" pin="CATHODE" pad="CATHODE"/>
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
<deviceset name="SERVO" prefix="J">
<gates>
<gate name="G$1" symbol="SERVO" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SERVO">
<connects>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="PULSE" pad="PULSE"/>
<connect gate="G$1" pin="VCC" pad="VCC"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="NE555P" prefix="U">
<gates>
<gate name="G$1" symbol="NE555P" x="0" y="0"/>
</gates>
<devices>
<device name="" package="DIP8">
<connects>
<connect gate="G$1" pin="CONT" pad="PIN_5"/>
<connect gate="G$1" pin="DISCH" pad="PIN_7"/>
<connect gate="G$1" pin="GND" pad="PIN_1"/>
<connect gate="G$1" pin="OUT" pad="PIN_3"/>
<connect gate="G$1" pin="RESET" pad="PIN_4"/>
<connect gate="G$1" pin="THRES" pad="PIN_6"/>
<connect gate="G$1" pin="TRIG" pad="PIN_2"/>
<connect gate="G$1" pin="VCC" pad="PIN_8"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="LM311P" prefix="U">
<gates>
<gate name="G$1" symbol="LM311P" x="0" y="0"/>
</gates>
<devices>
<device name="" package="DIP8">
<connects>
<connect gate="G$1" pin="BALANCE" pad="PIN_5"/>
<connect gate="G$1" pin="BAL_STROBE" pad="PIN_6"/>
<connect gate="G$1" pin="COL_OUT" pad="PIN_7"/>
<connect gate="G$1" pin="EMI_OUT" pad="PIN_1"/>
<connect gate="G$1" pin="GND" pad="PIN_4"/>
<connect gate="G$1" pin="IN+" pad="PIN_2"/>
<connect gate="G$1" pin="IN-" pad="PIN_3"/>
<connect gate="G$1" pin="VCC" pad="PIN_8"/>
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
<deviceset name="SB-NC" prefix="SB">
<gates>
<gate name="G$1" symbol="SB-NC" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SB-NC">
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
<deviceset name="JST-XH254-3P" prefix="J">
<gates>
<gate name="G$1" symbol="JST-XH254-3P" x="-5.08" y="0"/>
</gates>
<devices>
<device name="" package="JST-XH254-3P">
<connects>
<connect gate="G$1" pin="PIN1" pad="PIN1"/>
<connect gate="G$1" pin="PIN2" pad="PIN2"/>
<connect gate="G$1" pin="PIN3" pad="PIN3"/>
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
<deviceset name="JST-XH254-2P" prefix="J">
<gates>
<gate name="G$1" symbol="JST-XH254-2P" x="-5.08" y="0"/>
</gates>
<devices>
<device name="" package="JST-XH254-2P">
<connects>
<connect gate="G$1" pin="PIN1" pad="PIN1"/>
<connect gate="G$1" pin="PIN2" pad="PIN2"/>
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
<schematic_group name="SERVO1"/>
<schematic_group name="OUTDOOR_MODULE_CONNECTOR"/>
<schematic_group name="NEAR_HANDLE_MODULE_CONNECTOR"/>
<schematic_group name="SUPPLY_CONNECTOR"/>
</groups>
<parts>
<part name="D4" library="my_devices" deviceset="D_SCHOTTKY" device="" value="BAT41"/>
<part name="L1" library="my_devices" deviceset="L" device="" value="RLB0914-102KL, 1000 uH"/>
<part name="Q3" library="my_devices" deviceset="TRANSISTOR_PNP" device="" value="2N3906BU"/>
<part name="Q5" library="my_devices" deviceset="MOSFET_N" device="" value="STP14NM50N"/>
<part name="J1" library="my_devices" deviceset="SERVO" device="" value="MTR-SERVO-FS5103B"/>
<part name="U3" library="my_devices" deviceset="NE555P" device=""/>
<part name="GND11" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="Q4" library="my_devices" deviceset="TRANSISTOR_NPN" device="" value="2N3904"/>
<part name="GND15" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="C5" library="my_devices" deviceset="C" device="" value="10 uF"/>
<part name="R16" library="my_devices" deviceset="R" device="" value="3K"/>
<part name="C3" library="my_devices" deviceset="C-1" device="" value="10 pF"/>
<part name="GND16" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="R9" library="my_devices" deviceset="RD" device="" value="20K"/>
<part name="R11" library="my_devices" deviceset="R" device="" value="100"/>
<part name="C4" library="my_devices" deviceset="C-1" device="" value="80 pF"/>
<part name="Q2" library="my_devices" deviceset="TRANSISTOR_NPN" device="" value="2N3904"/>
<part name="R10" library="my_devices" deviceset="R" device="" value="200"/>
<part name="GND17" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="U2" library="my_devices" deviceset="LM311P" device=""/>
<part name="GND18" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="C1" library="my_devices" deviceset="C-1" device="" value="5nF"/>
<part name="R3" library="my_devices" deviceset="R" device="" value="150K"/>
<part name="C2" library="my_devices" deviceset="C" device="" value="1000 uF"/>
<part name="GND19" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="R14" library="my_devices" deviceset="R" device="" value="100"/>
<part name="GND23" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="R15" library="my_devices" deviceset="R" device="" value="5"/>
<part name="GND3" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="SW1" library="my_devices" deviceset="SWITCH" device=""/>
<part name="SB1" library="my_devices" deviceset="SB-NC" device="" value="KLS7-DS-01-B-00"/>
<part name="C6" library="my_devices" deviceset="C" device="" value="1000 uF"/>
<part name="GND4" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="D1" library="my_devices" deviceset="D_SCHOTTKY" device="" value="BAT41"/>
<part name="D2" library="my_devices" deviceset="D_SCHOTTKY" device="" value="BAT41"/>
<part name="J4" library="my_devices" deviceset="JST-XH254-3P" device="" value="JST-XH2.54-3P"/>
<part name="GND5" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="J2" library="my_devices" deviceset="JST-XH254-4P" device="" value="JST-XH2.54-4P"/>
<part name="GND1" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="J3" library="my_devices" deviceset="JST-XH254-2P" device="" value="JST-XH2.54-2P"/>
</parts>
<sheets>
<sheet>
<plain>
<text x="107.315" y="83.185" size="1.778" layer="91" grouprefs="SERVO1">~10-15-20V
In my case ~12..14V
Mosfet required &gt;8V</text>
</plain>
<instances>
<instance part="D4" gate="G$1" x="85.09" y="81.28" smashed="yes" grouprefs="SERVO1">
<attribute name="NAME" x="79.375" y="83.82" size="1.778" layer="94"/>
<attribute name="VALUE" x="79.375" y="77.47" size="1.778" layer="94"/>
</instance>
<instance part="L1" gate="G$1" x="69.85" y="86.36" smashed="yes" rot="R90" grouprefs="SERVO1">
<attribute name="NAME" x="69.215" y="88.265" size="1.778" layer="94" rot="R90"/>
<attribute name="VALUE" x="72.39" y="88.265" size="1.778" layer="94" rot="R90"/>
</instance>
<instance part="Q3" gate="G$1" x="-24.765" y="6.985" smashed="yes" grouprefs="SERVO1">
<attribute name="NAME" x="-20.955" y="8.255" size="1.778" layer="94"/>
<attribute name="VALUE" x="-20.955" y="4.445" size="1.778" layer="94"/>
</instance>
<instance part="Q5" gate="G$1" x="135.255" y="74.93" smashed="yes" rot="R90" grouprefs="SERVO1">
<attribute name="NAME" x="132.715" y="58.42" size="1.778" layer="94" rot="R90"/>
<attribute name="VALUE" x="140.335" y="58.42" size="1.778" layer="94" rot="R90"/>
</instance>
<instance part="J1" gate="G$1" x="142.24" y="35.56" smashed="yes" rot="R270" grouprefs="SERVO1">
<attribute name="VALUE" x="132.08" y="38.1" size="1.778" layer="94" rot="R270"/>
<attribute name="NAME" x="152.4" y="38.1" size="1.778" layer="94" rot="R270"/>
</instance>
<instance part="U3" gate="G$1" x="20.32" y="71.12" smashed="yes" rot="R180" grouprefs="SERVO1">
<attribute name="NAME" x="25.4" y="60.96" size="1.778" layer="94" rot="R180"/>
<attribute name="VALUE" x="25.4" y="78.74" size="1.778" layer="94" rot="R180"/>
</instance>
<instance part="GND11" gate="1" x="43.18" y="40.64" smashed="yes" grouprefs="SERVO1">
<attribute name="VALUE" x="40.64" y="38.1" size="1.778" layer="96"/>
</instance>
<instance part="Q4" gate="G$1" x="76.2" y="53.34" smashed="yes" grouprefs="SERVO1">
<attribute name="NAME" x="80.01" y="54.61" size="1.778" layer="94"/>
<attribute name="VALUE" x="80.01" y="50.8" size="1.778" layer="94"/>
</instance>
<instance part="GND15" gate="1" x="88.9" y="38.1" smashed="yes" grouprefs="SERVO1">
<attribute name="VALUE" x="86.36" y="35.56" size="1.778" layer="96"/>
</instance>
<instance part="C5" gate="G$1" x="96.52" y="68.58" smashed="yes" rot="R270" grouprefs="SERVO1">
<attribute name="NAME" x="101.6" y="73.66" size="1.778" layer="94" rot="R270"/>
<attribute name="VALUE" x="88.9" y="73.66" size="1.778" layer="94" rot="R270"/>
</instance>
<instance part="R16" gate="G$1" x="106.68" y="68.58" smashed="yes" rot="R90" grouprefs="SERVO1">
<attribute name="NAME" x="104.14" y="62.23" size="1.778" layer="94" rot="R90"/>
<attribute name="VALUE" x="110.49" y="62.23" size="1.778" layer="94" rot="R90"/>
</instance>
<instance part="C3" gate="G$1" x="10.16" y="91.44" smashed="yes" rot="R90" grouprefs="SERVO1">
<attribute name="NAME" x="6.985" y="86.995" size="1.778" layer="94" rot="R90"/>
<attribute name="VALUE" x="15.24" y="86.995" size="1.778" layer="94" rot="R90"/>
</instance>
<instance part="GND16" gate="1" x="19.05" y="93.98" smashed="yes" grouprefs="SERVO1">
<attribute name="VALUE" x="16.51" y="91.44" size="1.778" layer="96"/>
</instance>
<instance part="R9" gate="G$1" x="-38.1" y="78.74" smashed="yes" rot="R270" grouprefs="SERVO1">
<attribute name="NAME" x="-41.91" y="83.185" size="1.778" layer="94" rot="R270"/>
<attribute name="VALUE" x="-44.45" y="83.82" size="1.778" layer="94" rot="R270"/>
</instance>
<instance part="R11" gate="G$1" x="-27.94" y="86.36" smashed="yes" grouprefs="SERVO1">
<attribute name="NAME" x="-34.29" y="88.9" size="1.778" layer="94"/>
<attribute name="VALUE" x="-34.29" y="82.55" size="1.778" layer="94"/>
</instance>
<instance part="C4" gate="G$1" x="43.18" y="58.42" smashed="yes" rot="R90" grouprefs="SERVO1">
<attribute name="NAME" x="40.005" y="53.975" size="1.778" layer="94" rot="R90"/>
<attribute name="VALUE" x="48.26" y="53.975" size="1.778" layer="94" rot="R90"/>
</instance>
<instance part="Q2" gate="G$1" x="-43.18" y="-2.54" smashed="yes" grouprefs="SERVO1">
<attribute name="NAME" x="-39.37" y="-1.27" size="1.778" layer="94"/>
<attribute name="VALUE" x="-39.37" y="-5.08" size="1.778" layer="94"/>
</instance>
<instance part="R10" gate="G$1" x="-30.48" y="-10.16" smashed="yes" grouprefs="SERVO1">
<attribute name="NAME" x="-36.83" y="-7.62" size="1.778" layer="94"/>
<attribute name="VALUE" x="-36.83" y="-13.97" size="1.778" layer="94"/>
</instance>
<instance part="GND17" gate="1" x="-17.78" y="-12.7" smashed="yes" grouprefs="SERVO1">
<attribute name="VALUE" x="-20.32" y="-15.24" size="1.778" layer="96"/>
</instance>
<instance part="U2" gate="G$1" x="-71.12" y="22.86" smashed="yes" grouprefs="SERVO1">
<attribute name="NAME" x="-86.36" y="15.24" size="1.778" layer="94"/>
<attribute name="VALUE" x="-86.36" y="12.7" size="1.778" layer="94"/>
</instance>
<instance part="GND18" gate="1" x="-73.66" y="7.62" smashed="yes" grouprefs="SERVO1">
<attribute name="VALUE" x="-76.2" y="5.08" size="1.778" layer="96"/>
</instance>
<instance part="C1" gate="G$1" x="-99.06" y="25.4" smashed="yes" grouprefs="SERVO1">
<attribute name="NAME" x="-103.505" y="28.575" size="1.778" layer="94"/>
<attribute name="VALUE" x="-103.505" y="20.32" size="1.778" layer="94"/>
</instance>
<instance part="R3" gate="G$1" x="-86.36" y="33.02" smashed="yes" rot="R90" grouprefs="SERVO1">
<attribute name="NAME" x="-88.9" y="26.67" size="1.778" layer="94" rot="R90"/>
<attribute name="VALUE" x="-82.55" y="26.67" size="1.778" layer="94" rot="R90"/>
</instance>
<instance part="C2" gate="G$1" x="5.08" y="7.62" smashed="yes" rot="R270" grouprefs="SERVO1">
<attribute name="NAME" x="10.16" y="12.7" size="1.778" layer="94" rot="R270"/>
<attribute name="VALUE" x="-2.54" y="12.7" size="1.778" layer="94" rot="R270"/>
</instance>
<instance part="GND19" gate="1" x="5.08" y="-5.08" smashed="yes" grouprefs="SERVO1">
<attribute name="VALUE" x="2.54" y="-7.62" size="1.778" layer="96"/>
</instance>
<instance part="R14" gate="G$1" x="53.34" y="71.12" smashed="yes" grouprefs="SERVO1">
<attribute name="NAME" x="46.99" y="73.66" size="1.778" layer="94"/>
<attribute name="VALUE" x="46.99" y="67.31" size="1.778" layer="94"/>
</instance>
<instance part="GND23" gate="1" x="33.02" y="63.5" smashed="yes" grouprefs="SERVO1">
<attribute name="VALUE" x="30.48" y="60.96" size="1.778" layer="96"/>
</instance>
<instance part="R15" gate="G$1" x="76.2" y="71.12" smashed="yes" rot="R90" grouprefs="SERVO1">
<attribute name="NAME" x="73.66" y="64.77" size="1.778" layer="94" rot="R90"/>
<attribute name="VALUE" x="80.01" y="64.77" size="1.778" layer="94" rot="R90"/>
</instance>
<instance part="GND3" gate="1" x="96.52" y="-58.42" smashed="yes" grouprefs="SUPPLY_CONNECTOR">
<attribute name="VALUE" x="93.98" y="-60.96" size="1.778" layer="96"/>
</instance>
<instance part="SW1" gate="G$1" x="114.3" y="-50.8" smashed="yes" grouprefs="SUPPLY_CONNECTOR">
<attribute name="NAME" x="109.22" y="-45.72" size="1.778" layer="94"/>
<attribute name="VALUE" x="109.22" y="-55.88" size="1.778" layer="94"/>
</instance>
<instance part="SB1" gate="G$1" x="-83.82" y="-71.12" smashed="yes" grouprefs="OUTDOOR_MODULE_CONNECTOR">
<attribute name="NAME" x="-88.9" y="-73.66" size="1.778" layer="94"/>
<attribute name="VALUE" x="-88.9" y="-76.2" size="1.778" layer="94"/>
</instance>
<instance part="C6" gate="G$1" x="134.62" y="-58.42" smashed="yes" rot="R270" grouprefs="SUPPLY_CONNECTOR">
<attribute name="NAME" x="139.7" y="-53.34" size="1.778" layer="94" rot="R270"/>
<attribute name="VALUE" x="127" y="-53.34" size="1.778" layer="94" rot="R270"/>
</instance>
<instance part="GND4" gate="1" x="134.62" y="-66.04" smashed="yes" grouprefs="SUPPLY_CONNECTOR">
<attribute name="VALUE" x="132.08" y="-68.58" size="1.778" layer="96"/>
</instance>
<instance part="D1" gate="G$1" x="-38.1" y="63.5" smashed="yes" rot="R90">
<attribute name="NAME" x="-40.64" y="57.785" size="1.778" layer="94" rot="R90"/>
<attribute name="VALUE" x="-34.29" y="57.785" size="1.778" layer="94" rot="R90"/>
</instance>
<instance part="D2" gate="G$1" x="-27.94" y="60.96" smashed="yes" rot="R270">
<attribute name="NAME" x="-25.4" y="66.675" size="1.778" layer="94" rot="R270"/>
<attribute name="VALUE" x="-31.75" y="66.675" size="1.778" layer="94" rot="R270"/>
</instance>
<instance part="J4" gate="G$1" x="-104.14" y="-71.12" smashed="yes" rot="R180" grouprefs="OUTDOOR_MODULE_CONNECTOR">
<attribute name="NAME" x="-116.84" y="-73.66" size="1.778" layer="94" rot="R180"/>
<attribute name="VALUE" x="-116.84" y="-68.58" size="1.778" layer="94" rot="R180"/>
</instance>
<instance part="GND5" gate="1" x="-93.98" y="-78.74" smashed="yes" grouprefs="OUTDOOR_MODULE_CONNECTOR">
<attribute name="VALUE" x="-96.52" y="-81.28" size="1.778" layer="96"/>
</instance>
<instance part="J2" gate="G$1" x="-10.16" y="-76.2" smashed="yes" rot="R180" grouprefs="NEAR_HANDLE_MODULE_CONNECTOR">
<attribute name="NAME" x="-22.86" y="-78.74" size="1.778" layer="94" rot="R180"/>
<attribute name="NAME" x="-22.86" y="-78.74" size="1.778" layer="94" rot="R180"/>
<attribute name="VALUE" x="-22.86" y="-73.66" size="1.778" layer="94" rot="R180"/>
</instance>
<instance part="GND1" gate="1" x="2.54" y="-86.36" smashed="yes" grouprefs="NEAR_HANDLE_MODULE_CONNECTOR">
<attribute name="VALUE" x="0" y="-88.9" size="1.778" layer="96"/>
</instance>
<instance part="J3" gate="G$1" x="88.9" y="-53.34" smashed="yes" rot="R180" grouprefs="SUPPLY_CONNECTOR">
<attribute name="NAME" x="76.2" y="-55.88" size="1.778" layer="94" rot="R180"/>
<attribute name="VALUE" x="76.2" y="-50.8" size="1.778" layer="94" rot="R180"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="+5V" class="0">
<segment>
<pinref part="Q3" gate="G$1" pin="E"/>
<wire x1="-24.765" y1="-0.635" x2="-10.16" y2="-0.635" width="0.1524" layer="91" grouprefs="SERVO1"/>
<label x="-15.24" y="-2.54" size="1.778" layer="95" grouprefs="SERVO1"/>
</segment>
<segment>
<pinref part="Q5" gate="G$1" pin="D"/>
<wire x1="128.27" y1="72.39" x2="128.27" y2="62.23" width="0.1524" layer="91" grouprefs="SERVO1"/>
<label x="122.555" y="64.135" size="1.778" layer="95" grouprefs="SERVO1"/>
</segment>
<segment>
<pinref part="U2" gate="G$1" pin="VCC"/>
<pinref part="R3" gate="G$1" pin="P$2"/>
<wire x1="-86.36" y1="41.91" x2="-73.66" y2="41.91" width="0.1524" layer="91" grouprefs="SERVO1"/>
<wire x1="-73.66" y1="41.91" x2="-73.66" y2="33.02" width="0.1524" layer="91" grouprefs="SERVO1"/>
<wire x1="-73.66" y1="41.91" x2="-63.5" y2="41.91" width="0.1524" layer="91" grouprefs="SERVO1"/>
<junction x="-73.66" y="41.91" grouprefs="SERVO1"/>
<label x="-68.58" y="43.18" size="1.778" layer="95" grouprefs="SERVO1"/>
</segment>
<segment>
<pinref part="U2" gate="G$1" pin="IN-"/>
<wire x1="-81.28" y1="20.32" x2="-88.9" y2="20.32" width="0.1524" layer="91" grouprefs="SERVO1"/>
<label x="-88.9" y="20.32" size="1.778" layer="95" grouprefs="SERVO1"/>
</segment>
<segment>
<wire x1="124.46" y1="-50.8" x2="134.62" y2="-50.8" width="0.1524" layer="91" grouprefs="SUPPLY_CONNECTOR"/>
<label x="137.16" y="-50.8" size="1.778" layer="95" grouprefs="SUPPLY_CONNECTOR"/>
<pinref part="SW1" gate="G$1" pin="P$2"/>
<pinref part="C6" gate="G$1" pin="PIN_PLUS"/>
<wire x1="134.62" y1="-50.8" x2="142.24" y2="-50.8" width="0.1524" layer="91" grouprefs="SUPPLY_CONNECTOR"/>
<junction x="134.62" y="-50.8" grouprefs="SUPPLY_CONNECTOR"/>
</segment>
<segment>
<pinref part="SB1" gate="G$1" pin="P$2"/>
<wire x1="-73.66" y1="-71.12" x2="-60.96" y2="-71.12" width="0.1524" layer="91" grouprefs="OUTDOOR_MODULE_CONNECTOR"/>
<label x="-66.04" y="-71.12" size="1.778" layer="95" grouprefs="OUTDOOR_MODULE_CONNECTOR"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="PIN2"/>
<wire x1="-5.08" y1="-78.74" x2="17.78" y2="-78.74" width="0.1524" layer="91" grouprefs="NEAR_HANDLE_MODULE_CONNECTOR"/>
<label x="12.7" y="-78.74" size="1.778" layer="95" grouprefs="NEAR_HANDLE_MODULE_CONNECTOR"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="C4" gate="G$1" pin="P$1"/>
<wire x1="43.18" y1="50.8" x2="43.18" y2="43.18" width="0.1524" layer="91" grouprefs="SERVO1"/>
<pinref part="GND11" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="J1" gate="G$1" pin="GND"/>
<wire x1="76.2" y1="45.72" x2="88.9" y2="45.72" width="0.1524" layer="91" grouprefs="SERVO1"/>
<wire x1="88.9" y1="45.72" x2="96.52" y2="45.72" width="0.1524" layer="91" grouprefs="SERVO1"/>
<wire x1="96.52" y1="45.72" x2="106.68" y2="45.72" width="0.1524" layer="91" grouprefs="SERVO1"/>
<wire x1="106.68" y1="45.72" x2="137.16" y2="45.72" width="0.1524" layer="91" grouprefs="SERVO1"/>
<pinref part="GND15" gate="1" pin="GND"/>
<wire x1="88.9" y1="45.72" x2="88.9" y2="40.64" width="0.1524" layer="91" grouprefs="SERVO1"/>
<junction x="88.9" y="45.72" grouprefs="SERVO1"/>
<pinref part="Q4" gate="G$1" pin="E"/>
<pinref part="C5" gate="G$1" pin="PIN_GND"/>
<wire x1="96.52" y1="63.5" x2="96.52" y2="45.72" width="0.1524" layer="91" grouprefs="SERVO1"/>
<junction x="96.52" y="45.72" grouprefs="SERVO1"/>
<pinref part="R16" gate="G$1" pin="P$1"/>
<wire x1="106.68" y1="60.96" x2="106.68" y2="45.72" width="0.1524" layer="91" grouprefs="SERVO1"/>
<junction x="106.68" y="45.72" grouprefs="SERVO1"/>
</segment>
<segment>
<pinref part="C3" gate="G$1" pin="P$2"/>
<wire x1="10.16" y1="99.06" x2="19.05" y2="99.06" width="0.1524" layer="91" grouprefs="SERVO1"/>
<wire x1="19.05" y1="99.06" x2="19.05" y2="96.52" width="0.1524" layer="91" grouprefs="SERVO1"/>
<pinref part="GND16" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="R10" gate="G$1" pin="P$2"/>
<pinref part="GND17" gate="1" pin="GND"/>
<wire x1="-21.59" y1="-10.16" x2="-17.78" y2="-10.16" width="0.1524" layer="91" grouprefs="SERVO1"/>
</segment>
<segment>
<pinref part="U2" gate="G$1" pin="GND"/>
<pinref part="GND18" gate="1" pin="GND"/>
<wire x1="-73.66" y1="10.16" x2="-73.66" y2="12.7" width="0.1524" layer="91" grouprefs="SERVO1"/>
</segment>
<segment>
<pinref part="GND19" gate="1" pin="GND"/>
<pinref part="C2" gate="G$1" pin="PIN_GND"/>
<wire x1="5.08" y1="-2.54" x2="5.08" y2="2.54" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U3" gate="G$1" pin="GND"/>
<pinref part="GND23" gate="1" pin="GND"/>
<wire x1="30.48" y1="66.04" x2="33.02" y2="66.04" width="0.1524" layer="91" grouprefs="SERVO1"/>
</segment>
<segment>
<pinref part="GND3" gate="1" pin="GND"/>
<wire x1="93.98" y1="-55.88" x2="96.52" y2="-55.88" width="0.1524" layer="91" grouprefs="SUPPLY_CONNECTOR"/>
<pinref part="J3" gate="G$1" pin="PIN1"/>
</segment>
<segment>
<pinref part="C6" gate="G$1" pin="PIN_GND"/>
<pinref part="GND4" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="J4" gate="G$1" pin="PIN1"/>
<pinref part="GND5" gate="1" pin="GND"/>
<wire x1="-99.06" y1="-76.2" x2="-93.98" y2="-76.2" width="0.1524" layer="91" grouprefs="OUTDOOR_MODULE_CONNECTOR"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="PIN1"/>
<wire x1="-5.08" y1="-83.82" x2="2.54" y2="-83.82" width="0.1524" layer="91" grouprefs="NEAR_HANDLE_MODULE_CONNECTOR"/>
<pinref part="GND1" gate="1" pin="GND"/>
</segment>
</net>
<net name="SERVO_PWM_CONTROL" class="0">
<segment>
<pinref part="J1" gate="G$1" pin="PULSE"/>
<wire x1="147.32" y1="45.72" x2="147.32" y2="68.58" width="0.1524" layer="91" grouprefs="SERVO1"/>
<label x="149.86" y="48.26" size="1.778" layer="95" rot="R90" grouprefs="SERVO1"/>
</segment>
<segment>
<pinref part="C1" gate="G$1" pin="P$1"/>
<wire x1="-106.68" y1="25.4" x2="-127" y2="25.4" width="0.1524" layer="91" grouprefs="SERVO1"/>
<label x="-138.43" y="25.4" size="1.778" layer="95" grouprefs="SERVO1"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="PIN3"/>
<wire x1="-5.08" y1="-73.66" x2="17.78" y2="-73.66" width="0.1524" layer="91" grouprefs="NEAR_HANDLE_MODULE_CONNECTOR"/>
<label x="-2.54" y="-73.66" size="1.778" layer="95" grouprefs="NEAR_HANDLE_MODULE_CONNECTOR"/>
</segment>
</net>
<net name="N$39" class="0">
<segment>
<pinref part="D4" gate="G$1" pin="ANODE"/>
<wire x1="72.39" y1="81.28" x2="76.2" y2="81.28" width="0.1524" layer="91" grouprefs="SERVO1"/>
<pinref part="L1" gate="G$1" pin="P$2"/>
<pinref part="R15" gate="G$1" pin="P$2"/>
<wire x1="76.2" y1="81.28" x2="77.47" y2="81.28" width="0.1524" layer="91" grouprefs="SERVO1"/>
<wire x1="76.2" y1="80.01" x2="76.2" y2="81.28" width="0.1524" layer="91" grouprefs="SERVO1"/>
<junction x="76.2" y="81.28" grouprefs="SERVO1"/>
</segment>
</net>
<net name="N$40" class="0">
<segment>
<pinref part="J1" gate="G$1" pin="VCC"/>
<pinref part="Q5" gate="G$1" pin="S"/>
<wire x1="142.24" y1="45.72" x2="142.24" y2="72.39" width="0.1524" layer="91" grouprefs="SERVO1"/>
</segment>
</net>
<net name="N$44" class="0">
<segment>
<pinref part="U3" gate="G$1" pin="CONT"/>
<pinref part="C3" gate="G$1" pin="P$1"/>
<wire x1="10.16" y1="73.66" x2="10.16" y2="83.82" width="0.1524" layer="91" grouprefs="SERVO1"/>
</segment>
</net>
<net name="N$46" class="0">
<segment>
<pinref part="U3" gate="G$1" pin="TRIG"/>
<wire x1="30.48" y1="68.58" x2="38.1" y2="68.58" width="0.1524" layer="91" grouprefs="SERVO1"/>
<wire x1="38.1" y1="68.58" x2="38.1" y2="55.88" width="0.1524" layer="91" grouprefs="SERVO1"/>
<wire x1="38.1" y1="55.88" x2="-20.32" y2="55.88" width="0.1524" layer="91" grouprefs="SERVO1"/>
<pinref part="U3" gate="G$1" pin="THRES"/>
<wire x1="-20.32" y1="55.88" x2="-27.94" y2="55.88" width="0.1524" layer="91" grouprefs="SERVO1"/>
<wire x1="-27.94" y1="55.88" x2="-38.1" y2="55.88" width="0.1524" layer="91" grouprefs="SERVO1"/>
<wire x1="10.16" y1="71.12" x2="-20.32" y2="71.12" width="0.1524" layer="91" grouprefs="SERVO1"/>
<wire x1="-20.32" y1="71.12" x2="-20.32" y2="55.88" width="0.1524" layer="91" grouprefs="SERVO1"/>
<junction x="-20.32" y="55.88" grouprefs="SERVO1"/>
<wire x1="38.1" y1="68.58" x2="43.18" y2="68.58" width="0.1524" layer="91" grouprefs="SERVO1"/>
<junction x="38.1" y="68.58" grouprefs="SERVO1"/>
<pinref part="C4" gate="G$1" pin="P$2"/>
<wire x1="43.18" y1="68.58" x2="43.18" y2="66.04" width="0.1524" layer="91" grouprefs="SERVO1"/>
<pinref part="D1" gate="G$1" pin="ANODE"/>
<pinref part="D2" gate="G$1" pin="CATHODE"/>
<junction x="-27.94" y="55.88"/>
</segment>
</net>
<net name="N$47" class="0">
<segment>
<pinref part="U3" gate="G$1" pin="DISCH"/>
<wire x1="-27.94" y1="68.58" x2="10.16" y2="68.58" width="0.1524" layer="91" grouprefs="SERVO1"/>
<pinref part="R9" gate="G$1" pin="P3"/>
<wire x1="-27.94" y1="68.58" x2="-27.94" y2="78.74" width="0.1524" layer="91" grouprefs="SERVO1"/>
<wire x1="-27.94" y1="78.74" x2="-30.48" y2="78.74" width="0.1524" layer="91" grouprefs="SERVO1"/>
<pinref part="D2" gate="G$1" pin="ANODE"/>
<junction x="-27.94" y="68.58"/>
</segment>
</net>
<net name="N$48" class="0">
<segment>
<pinref part="R9" gate="G$1" pin="P2"/>
<wire x1="-38.1" y1="71.12" x2="-38.1" y2="68.58" width="0.1524" layer="91" grouprefs="SERVO1"/>
<pinref part="D1" gate="G$1" pin="CATHODE"/>
</segment>
</net>
<net name="N$49" class="0">
<segment>
<pinref part="R9" gate="G$1" pin="P1"/>
<pinref part="R11" gate="G$1" pin="P$1"/>
<wire x1="-38.1" y1="86.36" x2="-35.56" y2="86.36" width="0.1524" layer="91" grouprefs="SERVO1"/>
</segment>
</net>
<net name="N$51" class="0">
<segment>
<pinref part="D4" gate="G$1" pin="CATHODE"/>
<wire x1="96.52" y1="81.28" x2="90.17" y2="81.28" width="0.1524" layer="91" grouprefs="SERVO1"/>
<junction x="96.52" y="81.28" grouprefs="SERVO1"/>
<pinref part="C5" gate="G$1" pin="PIN_PLUS"/>
<wire x1="96.52" y1="76.2" x2="96.52" y2="81.28" width="0.1524" layer="91" grouprefs="SERVO1"/>
<pinref part="Q5" gate="G$1" pin="G"/>
<wire x1="96.52" y1="81.28" x2="106.68" y2="81.28" width="0.1524" layer="91" grouprefs="SERVO1"/>
<wire x1="106.68" y1="81.28" x2="137.795" y2="81.28" width="0.1524" layer="91" grouprefs="SERVO1"/>
<pinref part="R16" gate="G$1" pin="P$2"/>
<wire x1="106.68" y1="77.47" x2="106.68" y2="81.28" width="0.1524" layer="91" grouprefs="SERVO1"/>
<junction x="106.68" y="81.28" grouprefs="SERVO1"/>
</segment>
</net>
<net name="N$37" class="0">
<segment>
<pinref part="Q2" gate="G$1" pin="C"/>
<pinref part="Q3" gate="G$1" pin="B"/>
<wire x1="-43.18" y1="5.08" x2="-43.18" y2="6.985" width="0.1524" layer="91" grouprefs="SERVO1"/>
<wire x1="-43.18" y1="6.985" x2="-32.385" y2="6.985" width="0.1524" layer="91" grouprefs="SERVO1"/>
</segment>
</net>
<net name="N$38" class="0">
<segment>
<pinref part="Q2" gate="G$1" pin="E"/>
<pinref part="R10" gate="G$1" pin="P$1"/>
<wire x1="-43.18" y1="-10.16" x2="-38.1" y2="-10.16" width="0.1524" layer="91" grouprefs="SERVO1"/>
</segment>
</net>
<net name="N$50" class="0">
<segment>
<pinref part="U2" gate="G$1" pin="EMI_OUT"/>
<pinref part="Q2" gate="G$1" pin="B"/>
<wire x1="-63.5" y1="22.86" x2="-50.8" y2="22.86" width="0.1524" layer="91" grouprefs="SERVO1"/>
<wire x1="-50.8" y1="22.86" x2="-50.8" y2="-2.54" width="0.1524" layer="91" grouprefs="SERVO1"/>
</segment>
</net>
<net name="N$53" class="0">
<segment>
<pinref part="C1" gate="G$1" pin="P$2"/>
<pinref part="U2" gate="G$1" pin="IN+"/>
<wire x1="-91.44" y1="25.4" x2="-86.36" y2="25.4" width="0.1524" layer="91" grouprefs="SERVO1"/>
<pinref part="R3" gate="G$1" pin="P$1"/>
<wire x1="-86.36" y1="25.4" x2="-81.28" y2="25.4" width="0.1524" layer="91" grouprefs="SERVO1"/>
<junction x="-86.36" y="25.4" grouprefs="SERVO1"/>
</segment>
</net>
<net name="+5V_IF_EN" class="0">
<segment>
<pinref part="Q3" gate="G$1" pin="C"/>
<wire x1="-24.765" y1="14.605" x2="-24.765" y2="15.24" width="0.1524" layer="91" grouprefs="SERVO1"/>
<wire x1="-24.765" y1="15.24" x2="5.08" y2="15.24" width="0.1524" layer="91" grouprefs="SERVO1"/>
<pinref part="C2" gate="G$1" pin="PIN_PLUS"/>
<junction x="5.08" y="15.24" grouprefs="SERVO1"/>
<wire x1="5.08" y1="15.24" x2="33.02" y2="15.24" width="0.1524" layer="91" grouprefs="SERVO1"/>
<label x="20.32" y="15.875" size="1.778" layer="95" grouprefs="SERVO1"/>
</segment>
<segment>
<pinref part="R11" gate="G$1" pin="P$2"/>
<wire x1="-19.05" y1="86.36" x2="-1.27" y2="86.36" width="0.1524" layer="91" grouprefs="SERVO1"/>
<label x="-14.605" y="86.995" size="1.778" layer="95" grouprefs="SERVO1"/>
</segment>
<segment>
<pinref part="L1" gate="G$1" pin="P$1"/>
<wire x1="67.31" y1="81.28" x2="58.42" y2="81.28" width="0.1524" layer="91" grouprefs="SERVO1"/>
<wire x1="58.42" y1="81.28" x2="58.42" y2="99.06" width="0.1524" layer="91" grouprefs="SERVO1"/>
<label x="45.085" y="99.695" size="1.778" layer="95" grouprefs="SERVO1"/>
<wire x1="58.42" y1="99.06" x2="48.895" y2="99.06" width="0.1524" layer="91" grouprefs="SERVO1"/>
<pinref part="U3" gate="G$1" pin="RESET"/>
<wire x1="30.48" y1="73.66" x2="30.48" y2="81.28" width="0.1524" layer="91" grouprefs="SERVO1"/>
<wire x1="30.48" y1="81.28" x2="58.42" y2="81.28" width="0.1524" layer="91" grouprefs="SERVO1"/>
<junction x="58.42" y="81.28" grouprefs="SERVO1"/>
</segment>
<segment>
<pinref part="U3" gate="G$1" pin="VCC"/>
<wire x1="10.16" y1="66.04" x2="-1.27" y2="66.04" width="0.1524" layer="91" grouprefs="SERVO1"/>
<label x="-2.54" y="63.5" size="1.778" layer="95" grouprefs="SERVO1"/>
</segment>
</net>
<net name="N$35" class="0">
<segment>
<pinref part="U3" gate="G$1" pin="OUT"/>
<pinref part="R14" gate="G$1" pin="P$1"/>
<wire x1="30.48" y1="71.12" x2="45.72" y2="71.12" width="0.1524" layer="91" grouprefs="SERVO1"/>
</segment>
</net>
<net name="N$1" class="0">
<segment>
<pinref part="Q4" gate="G$1" pin="C"/>
<pinref part="R15" gate="G$1" pin="P$1"/>
<wire x1="76.2" y1="60.96" x2="76.2" y2="63.5" width="0.1524" layer="91" grouprefs="SERVO1"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="R14" gate="G$1" pin="P$2"/>
<pinref part="Q4" gate="G$1" pin="B"/>
<wire x1="62.23" y1="71.12" x2="62.23" y2="53.34" width="0.1524" layer="91" grouprefs="SERVO1"/>
<wire x1="62.23" y1="53.34" x2="68.58" y2="53.34" width="0.1524" layer="91" grouprefs="SERVO1"/>
</segment>
</net>
<net name="OUTDOOR_SIGNAL" class="0">
<segment>
<pinref part="J4" gate="G$1" pin="PIN3"/>
<wire x1="-99.06" y1="-66.04" x2="-66.04" y2="-66.04" width="0.1524" layer="91" grouprefs="OUTDOOR_MODULE_CONNECTOR"/>
<label x="-83.82" y="-66.04" size="1.778" layer="95" grouprefs="OUTDOOR_MODULE_CONNECTOR"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="PIN4"/>
<wire x1="-5.08" y1="-68.58" x2="17.78" y2="-68.58" width="0.1524" layer="91" grouprefs="NEAR_HANDLE_MODULE_CONNECTOR"/>
<label x="-2.54" y="-68.58" size="1.778" layer="95" grouprefs="NEAR_HANDLE_MODULE_CONNECTOR"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<wire x1="93.98" y1="-50.8" x2="104.14" y2="-50.8" width="0.1524" layer="91" grouprefs="SUPPLY_CONNECTOR"/>
<pinref part="SW1" gate="G$1" pin="P$1"/>
<pinref part="J3" gate="G$1" pin="PIN2"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="J4" gate="G$1" pin="PIN2"/>
<pinref part="SB1" gate="G$1" pin="P$1"/>
<wire x1="-99.06" y1="-71.12" x2="-93.98" y2="-71.12" width="0.1524" layer="91" grouprefs="OUTDOOR_MODULE_CONNECTOR"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
<errors>
<approved hash="104,1,142.24,45.72,J1,VCC,N$40,,,"/>
<approved hash="104,1,10.16,66.04,U3,VCC,+5V_IF_EN,,,"/>
<approved hash="104,1,-73.66,33.02,U2,VCC,+5V,,,"/>
<approved hash="202,1,-63.5,17.78,U2,BAL_STROBE,,,,"/>
<approved hash="202,1,-63.5,15.24,U2,BALANCE,,,,"/>
</errors>
</schematic>
</drawing>
<compatibility>
<note version="6.3" minversion="6.2.2" severity="warning">
Since Version 6.2.2 text objects can contain more than one line,
which will not be processed correctly with this version.
</note>
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
