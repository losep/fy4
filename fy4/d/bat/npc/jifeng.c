#include <ansi.h> 
inherit NPC;  
void create()  
{  
 int ni;  
 ni=1+random(36);  
 set_name("疾风第"+chinese_number(ni)+"骑", ({ "qishi"}));  
 set("long", "果然是条好汉，只见洒金斗篷，织锦劲装，胸前各有一面  
 紫铜护心镜，镜上刻着个数字。\n");  
 set("title","快活王座前护卫");  
 set("gender", "男性");  
 set("age", (30-ni/3));  
 set("attitude", "friendly");  
 set("SEN", -500-random(1000));  
 set("str", 30);  
 set("per",28);  
 set_skill("sword",(110-ni));  
// set_skill("deisword",(100-ni));  
// map_skill("sword","deisword"); 
 set("combat_exp", (30000*(36-ni))); 
 setup();  
 carry_object("obj/weapon/sword")->wield();  
 carry_object("/obj/armor/armor_huxinjing", ([ "name"   : "第"+chinese_number(ni)+"护心镜" ]))->wear();  
 }  
  
     
