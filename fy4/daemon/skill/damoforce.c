 // Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
#include <ansi.h>
inherit SKILL;
void setup() {
        set("name", "达摩易筋经");
        set("usage/force", 1);
        set("skill_class", "shaolin");
        set("effective_level", 320);
        set("learn_bonus", -20);
        set("practice_bonus", -10);
        set("black_white_ness", 30);
}  
void skill_improved(object me)
{
        int s; 
        s = me->query_skill("damoforce", 1);
        if(!(s%10) && (int)me->query("con") < s/4){ 
                tell_object(me, HIG
"你学着学着达摩易筋经，突然感到丹田之气喷涌而出！！\n" NOR);
                me->add("con", 1);
                me->unconcious();
        }
}       
