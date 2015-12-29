#include <ansi.h>
inherit "/d/taiping/npc/smart_npc"; 
void create()
{ 
        set_name("���к�",({"yunzhong he","yunzhong","he"}));
        set("title",WHT"�����嶾"NOR);
        set("long", "�����嶾֮�ף�ԭ���䵱�Ļ��̳��ϣ���̰��Ůɫ��ʯ�������ϳ�����
�˱䱾����������һ����ζ��Ͷ֮�ɻ������㼣�鲼��ԭ��\n");
        set("age",59);
        set("gender","����");
        set("combat_exp", 7000000);
         set("attitude", "aggressive");
        
        set("max_atman", 1000);
        set("atman", 1000);
        set("max_mana", 1000);
        set("mana", 1000);
        set("max_force",2000);
        set("force",2000);
        set("force_factor",100); 
        set("str",40);
        set("cor", 40);
        set("cps", 40);
        set("agi",40);
        set("fle",100);
        
        set("no_fly",1);
        
        set("resistance/gin",30);
        set("resistance/kee",50);
        set("resistance/sen",40);
        
//      setting up special NPC function: healer, defense, zombie-killer
//      defense_type: 1. xiaohun-sword; 2.xiaohun-whip;3 yue-strike;4 lingxi-zhi;
        
        set("defense_type",random(2)+1);        
//      set("zombie-killer",1);
//      set("officer-killer",1);
//      set("dungeon_npc","check");
        
   set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: auto_smart_fight() :),    
        }) );
         
        CHAR_D->setup_char(this_object());
        auto_npc_setup("liaoyin",250,200,1,"/obj/weapon/","fighter_w","tanzhi-shentong",1);
        setup();
        carry_object("/obj/armor/cloth")->wear();
}  
int heal_up()
{
        if( environment() && !is_fighting() ) {
                call_out("leave", 1);
                return 1;
        }
        return ::heal_up() + 1;
} 
void leave()
{
        object another;
        message("vision",name() + "�����һЦ���ֳ����Ǹ��������⣬����һ�Ѵ���ӵĺ��ƹ�\n", 
                environment(),this_object() );
        environment(this_object())->reset();
//      another = new(__DIR__"bosshu");
//      another->move(environment(this_object()));
        destruct(this_object());
}  
void die()
{
        object me, owner;
        if(objectp(me=query_temp("last_damage_from") ))     
        if(owner=me->query("possessed")) {
                me = owner;
        } 
        if(me->query("wanma/�ײ�֮��"))
                        me->set_temp("wanma/�����嶾e",1);
        ::die();
}   