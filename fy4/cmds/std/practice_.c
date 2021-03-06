重新分布所有使命．．．．．．重新分布完毕 
 // practice.c
#include <ansi.h> 
inherit F_CLEAN_UP; 
int main(object me, string arg)
{
    string p_skill, skillname;
    int skill, skill_basic;
    int amount, times;
    int o_kee, o_gin, o_sen, o_force, o_mana, o_atman;
    int c_kee, c_gin, c_sen, c_force, c_mana, c_atman;    
    int p_kee, p_gin, p_sen, p_force, p_mana, p_atman;
    
    seteuid(getuid());
    if(environment(me)->query("no_fight"))
        return notify_fail("你不可以在这里练习。\n");
    if( me->is_fighting() )
        return notify_fail("你已经在战斗中了，学一点实战经验吧。\n");
    
    if(!arg)
        return notify_fail("指令格式：practice <技能> || practice <技能> <练习次数>\n");     
    if (sscanf(arg, "%s %d", p_skill, times)!=2)  p_skill = arg; 
    if( !p_skill ) return (__DIR__"enable")->main(me, p_skill);
    
    if( !stringp(skillname = me->query_skill_mapped(p_skill)) )
        return notify_fail("你只能练习用 enable 指定的特殊技能。\n"); 
    skill_basic = me->query_skill(p_skill,1)/2 + 1;
    skill = me->query_skill(skillname) + 1;
    
    if( skill < 1 )
        return notify_fail("你好像还没「学会」这项技能吧？最好先去请教别人。\n");
    if( skill_basic < 1 )
        return notify_fail("你对这方面的技能还是一窍不通，最好从先从基本学起。\n");
    
    write("BW:" + (string) SKILL_D(skillname)->black_white_ness() +"\n"
    + "Bonus" + (string) SKILL_D(skillname)->practice_bonus()+"\n"
    + "times: " + (string) times +"\n"
    + p_skill + "\n");
    
    if( !SKILL_D(skillname)->valid_learn(me) ) return 0; 
    notify_fail("你试著练习" + SKILL_D(skillname)->name() + "，但是并没有任何进步。\n");
    if ( times >1) {
        o_kee = me->query("kee");
        o_gin = me->query("gin");
        o_sen = me->query("sen");
        o_force = me->query("force");
        o_mana = me->query("mana");
        o_atman = me->query("atman");
        //<- get status before 1 practicing
        
        //-> Start multi-practicing
        if(SKILL_D(skillname)->practice_skill(me)) {
                c_kee = me->query("kee");
                c_gin = me->query("gin");
                c_sen = me->query("sen");
                c_force = me->query("force");
                c_mana = me->query("mana");
                c_atman = me->query("atman");
                //<- immediately get current status after 1 practicing
                p_kee = o_kee - c_kee;
                p_gin = o_gin - c_gin;
                p_sen = o_sen - c_sen;
                p_force = o_force - c_force;
                p_mana = o_mana - c_mana;
                p_atman = o_atman - c_atman;
                //<- get the consumption
                if (p_kee) times = (times > c_kee/p_kee) ? c_kee/p_kee: times;
                if (p_gin) times = (times > c_gin/p_gin) ? c_gin/p_gin: times;
                if (p_sen) times = (times > c_sen/p_sen) ? c_sen/p_sen: times;
                if (p_force) times = (times > c_force/p_force) ? c_force/p_force: times;
                if (p_mana) times = (times > c_mana/p_mana) ? c_mana/p_mana: times;
                if (p_atman) times = (times > c_atman/p_atman) ? c_atman/p_atman: times;
                // <- get the least numbers allowed to practice
                if (p_kee) me->add("kee", -p_kee * (times-1));
                if (p_gin) me->add("gin", -p_gin * (times-1));
                if (p_sen) me->add("sen", -p_sen * (times-1));
                if (p_force) me->add("force", -p_force * (times-1));
                if (p_mana) me->add("mana", -p_mana * (times-1));
                if (p_atman) me->add("atman", -p_atman * (times-1));
                // <- receive the practice damage
                write("real time:" + (string) times + "\n");
                   if (times > 0) {
                        amount = (skill - 75) * SKILL_D(skillname)->black_white_ness()/100;
                        if((amount < -25) && (skill < 75)) amount = -25;
                        amount +=SKILL_D(skillname)->practice_bonus() + skill_basic/5 + 1;
                        if( amount < 1) amount = 1;
                        me->improve_skill(skillname, amount*times + random(1 + times/5), skill_basic > skill? 0: 1);
                        // <- random(1 + times/5) ***** giving a bit bonus for saving system resource
                        write( HIY "你的" + SKILL_D(skillname)->name() + "进步了！\n" NOR);
                        return 1;
                }
                else return notify_fail("你的身体状况无法强化练习" + SKILL_D(skillname)->name() + "。\n");
        }
    }
    else {
        if(SKILL_D(skillname)->practice_skill(me)) {
                amount = (skill - 75) * SKILL_D(skillname)->black_white_ness()/100;
                if((amount < -25) && (skill < 75)) amount = -25;
                amount +=SKILL_D(skillname)->practice_bonus() + skill_basic/5 + 1;
                if( amount < 1) amount = 1;
                me->improve_skill(skillname, amount, skill_basic > skill? 0: 1);
                write( HIY "你的" + SKILL_D(skillname)->name() + "进步了！\n" NOR);
                return 1;
        }
    }
    return 0;    
} 
int help(object me)
{
    write(@TEXT
指令格式：practice <技能种类> || practice <技能> <练习次数> 
这个指令让你练习某个种类的技能，这个技能必须是经过 enable 的专业技能。 
如果你对这方面的基本技能够高，可以经由练习直接升级，而且升级的上限只跟
你基本技能的等级有关，换句话说，勤加练习是使你的所学「青出於蓝胜於蓝」
的唯一途径，当然，在这之前你必须从实际运用中获得足够的经验以提升你的基
本技能。
TEXT
        );
    return 1;
}      
