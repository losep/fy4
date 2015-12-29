 // roar.c
#include <ansi.h> 
inherit F_CLEAN_UP; 
int exert(object me, object target, int amount)
{
        object *ob;
        int i, skill, damage; 
        if( !me->is_fighting() )
                return notify_fail("�����Ϸ�ţ�ֻ����ս����ʹ�á�\n"); 
        if( (int)me->query("force") < 150 )
                return notify_fail("�������������\n"); 
        skill = me->query_skill("force"); 
        me->add("force", -150);
        me->receive_damage("kee", 10); 
        me->start_busy(7);
        message_vision(
                HIR "$N�����ͻȻӽ���ͳ������ķ�ţ�\n" NOR, me);
        if(environment(me)->query("no_fight") ||
           environment(me)->query("no_magic") ||
           environment(me)->query("no_spells")
        )
                return notify_fail("���ﲻ���÷�š�\n");
        ob = all_inventory(environment(me));
        for(i=0; i<sizeof(ob); i++) {
                if( !living(ob[i]) || ob[i]==me ) continue;
                if( skill/2 + random(skill/2) < (int)ob[i]->query("cps") * 2 ) continue;
                
                damage = skill - ((int)ob[i]->query("max_force") / 10);
                if( damage > 0 ) {
                        ob[i]->receive_damage("sen", damage);
                        if( (int)ob[i]->query("force") < skill * 2 )
                                ob[i]->receive_wound("sen", damage);
                        message_vision("$N����ͷʹ���ѣ��������˹�ȥ��\n",ob[i]);
                }
                
                if( userp(ob[i]) ) ob[i]->fight_ob(me);
                else if( !ob[i]->is_killing(me) ) ob[i]->kill_ob(me);
        } 
        return 1;
}     