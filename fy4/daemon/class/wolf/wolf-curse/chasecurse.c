#include <ansi.h>
inherit SSERVER;
int curse(object me, object target)
{
        string msg;
        int damage,level,perp;
        object ob, room; 
        if(me->query("class")!="wolfmount")
                return notify_fail("只有狼山弟子才能使出「蹑降」。\n");
        level=(int)me->query_skill("wolf-curse",1);
        if(level < 100 )
                return notify_fail("你的降头术不够高！\n");
        
        if(!target) return notify_fail("你想向谁下这个降头？\n");
        room=environment(target);
        if(room!=environment(me)) 
                return notify_fail("你想向谁下这个降头？\n");
        
        if ( environment(me)->query("no_fly") || environment(target)->query("no_fly"))
                return notify_fail("此地不能使用蹑降。\n"); 
        if (userp(target))
                return notify_fail("蹑降不能用在玩家身上。\n");
        if(! target->is_character())
                return notify_fail("追踪这个东西？你是不是觉得很无聊？\n"); 
        
        if (domain_file(file_name(environment(target)))=="eren2")
                return notify_fail("此人警觉太高，无法下蹑降。\n");
        if (target->is_corpse())
                return notify_fail("你只能向活物下这个降头。\n");
                
        if((int)me->query("kee") < 100 )
                return notify_fail("你的气血不够！\n");
        
        me->receive_damage("kee",100);
        me->start_busy(2);
        if(random(me->query("combat_exp"))>target->query("combat_exp")/4)
                {
                me->set_temp("chase_target",target);
                target->set_temp("chaser",me);
                perp=target->query_skill("perception",1);
           if (random(perp)>level/2) target->start_call_out( (: call_other, __FILE__, "warning", target:), 3);
                tell_object(me,HIW"你已经成功的对"+target->name()+"下了蹑降。\n"NOR);
                return 1;
                }
        else return notify_fail(HIW"你由于不够熟练而失败了。\n"NOR);
}
                
                
                
void warning(object target)
{
        tell_object(target,HIR"      好像有人在暗中盯住了你.\n"NOR);
}      
