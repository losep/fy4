#include <ansi.h>
inherit F_CLEAN_UP;  
int exert(object me,object target,int amount)
{
        int extra; 
        if(me->query("class")!="shenshui"&& userp(me))
                return notify_fail("只有神水宫弟子才能使出「九阴凝寒」的绝技。\n");
        
        if(me->query_temp("nine-moon-force_poison"))
                return notify_fail("你已经在施展「九阴凝寒」了。\n");
        
        if (me->query_skill("nine-moon-force",1)<150)
                return notify_fail("你的九阴心经太差。\n");
        
        if (me->query_skill("nine-moon-claw",1)<120)
                return notify_fail("你的九阴白骨抓不够熟练。\n");
                
        if (me->query_skill("nine-moon-spirit",1)<150)
                return notify_fail("你的姹女神功不够熟练。\n");
        
        if (me->query("force") < 300)
                return notify_fail("你的内力不够。\n");
        
        extra = me->query_skill("force");
        extra= extra+random(extra);
        extra= extra*2;
             
        me->add("force", -300);
        message_vision(MAG"$N瞑目屏息，运起九阴心经，一层淡淡的雾气在$N周围一闪即逝。\n"NOR,me);
        
        
        me->add_temp("nine-moon-force_poison",extra);
        call_out("remove_effect",extra/5,me,extra);
        return 1;
} 
int remove_effect(object me,int extra)
{
        if(!me) return 0;
        me->add_temp("nine-moon-force_poison",-extra);
        tell_object(me,"你的「九阴凝寒」功效消失了。。\n");
   return 1;
}  
