 // tie@fengyun
#include <ansi.h>
#include <combat.h>
inherit F_CLEAN_UP;
void remove_effect(object me, int amount);
int perform(object me, object target)
{
        int skill;
                if(!target) target=me;
        if(me->query("class")!="fugui")
                return notify_fail("只有富贵山庄弟子才能使出「金钟罩」的绝技。\n");
        if(me->query("gender")!="男性")
                return notify_fail("这是男人练的功夫，你‘罩‘什么？？\n");     
       if( target != me ) return 
                    notify_fail("你只能将『金钟罩』用在自己的身上。\n");
        if( (int)me->query("force") < 200 )     return
                        notify_fail("你的内力不够。\n");
        if( (int)me->query_temp("daoqian") ) return 
                        notify_fail("你已经在施展『金钟罩』了。\n");
        skill = me->query_skill("henglian",1);
        if(skill < 100) return notify_fail("你的十三太保横练功太差了！\n");
        skill = random(skill/2)+skill/2;
        me->add("force", -150);
        message_vision( 
HIY"$N提气耸身，全身骨节一阵阵爆响，整个身形赫然大了一圈！！\n" NOR, me);
        me->add_temp("apply/iron-cloth", skill);
        me->set_temp("daoqian", 1);
        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, 
skill :), skill);
        if( me->is_fighting() ) me->start_busy(3);
        return 1;
} 
void remove_effect(object me, int amount)
{
        me->add_temp("apply/iron-cloth", - amount);
        me->delete_temp("daoqian");
        if( me->is_fighting() ) me->start_busy(1);      
        tell_object(me, "你的『金钟罩』功效散光了。\n");
}
     
