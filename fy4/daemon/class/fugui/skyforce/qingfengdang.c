 // soulheal.c
#include <ansi.h> 
int exert(object me, object target, int amount)
{
        if( !target )
                return notify_fail("你要用真气为谁疗伤？\n"); 
        if( me->is_fighting() || target->is_fighting())
        return notify_fail("战斗中无法运用『清风荡』疗伤！\n"); 
        if( (int)me->query("force")< 600 )
                return notify_fail("你的真气不够。\n"); 
        if (target!=me)
                message_vision(
        HIG "$N双手十支手指冒出丝丝冷气，瞬间连点$n全身三十六道大穴....\n"
        "片刻之后，$n感觉清风拂面，快意盎然，深呼一口气，精神看起来好多了。\n" NOR,
                me, target );
        else
                message_vision(
        HIG "$N双手十支手指冒出丝丝冷气，瞬间连点自身三十六道大穴....\n"
        "片刻之后，$N感觉清风拂面，快意盎然，深呼一口气，精神看起来好多了。\n" NOR,
                me); 
        target->receive_curing("gin", 5 + (int)me->query_skill("force"));
        me->add("force", -150);
        me->set("force_factor", 0); 
        return 1;
}     
