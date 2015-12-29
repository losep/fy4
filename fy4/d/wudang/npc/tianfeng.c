#include <ansi.h>
inherit F_MASTER;
inherit NPC;
void imbue_event(object me);
void create()
{
        set_name("���ʮ����", ({ "master tianfeng", "tianfeng", "master"}) );
        set("gender", "����" );
        set("age", 55);
        set("nickname", CYN "��������" NOR);
        set("long", 
"һ����ɫ���ƣ�Ũü��ȧ���������ߣ���������ɱ��������ϥ����ɽ��֮�ϣ�
�¾���¶�����㣬ȴ��һ˫�߳���ľ��ľ��˷���ǰ��ľ���Ͼ��ַ��ű���
�ʳ�����\n");
        create_family("һ����", 7, "�Ҷ�");
    set("rank_nogen",1);
    set("ranks",({"����","����","����",RED"��ɲ"NOR,HIR"����"NOR}));
    set("rank_levels",({32000,512000,1536000,3456000 }));
        set("combat_exp", 5000000);
        set("attitude", "friendly");
        set("reward_npc", 1);
        set("difficulty", 30);
        set("force", 2000);
        set("max_force",2000);
        set("force_factor",60);
        
        set_skill("unarmed", 140);
        set_skill("ghosty-force", 300);
        set_skill("enmeiryu",120);
        set_skill("ittouryu",160);
        set_skill("ninjitsu",200);
        set_skill("dodge", 180);
        set_skill("ghosty-steps",200);
        set_skill("blade",160);
        set_skill("literate", 140);
        set_skill("force", 180);
        set_skill("parry", 140);
        set_skill("magic", 100);
        
        map_skill("magic", "ninjitsu");
           map_skill("unarmed", "enmeiryu");
        map_skill("blade", "ittouryu");
        map_skill("parry", "ittouryu");
        map_skill("force", "ghosty-force");
        
        
        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: perform_action, "unarmed.mukuha" :),
                (: perform_action,"unarmed.shiden" :),
                (: perform_action, "unarmed.shimon" :),  
                (: perform_action, "blade.gobankiri" :), 
                (: perform_action, "blade.hyakki" :), 
                           
             }) ); 
   
   
   
        set_temp("apply/damage",100);
        set("chat_chance", 1);
        set("chat_msg", ({
                        "���ʮ������ب�Ų��������ɫ����ͻȻ�����������۵�һ���ȳ�����Ѫ��\n",
                                })  );
        set("inquiry",  ([
                "���" : "���ӡ������ӡ��������������\n",
                "�Ϲ���" : "��ʧɢ����ĺ��Ӱ�������֮������ܼ���һ����Ҳ�޺�����\n",
                "�޻�" : "��ʧɢ����ĺ��Ӱ�������֮������ܼ���һ����Ҳ�޺�����\n",
                ])              ); 
        setup();
    carry_object(__DIR__"obj/wucloth")->wear();
    carry_object(__DIR__"obj/muji")->wear();
        carry_object(__DIR__"obj/blackblade")->wield();
} 
void init()
{       object ob;
        ::init();
        add_action("do_answer","answer");
        if( interactive(ob = this_player()) && !is_fighting() ) 
        if (ob->query("���_quest6")&&ob->query("class")!="ninja")
        {
                remove_call_out("recruiting");
                call_out("recruiting", 1, ob);
        } 
}  
void win_enemy(object loser)
{
    message_vision(HIC "���ʮ�������쳤̾һ�������á���\n"NOR,loser);
    message_vision(HIR "���ʮ����ͻȻ�۵�һ���������Ѫ������һ�����쳤˻��
���Ӱ����㡣�����㡣���ںη�����\n"NOR,loser);
        loser->set("���_quest1",time());
} 
void lose_enemy( object winner)
{
        object blade;
        
        winner->set("���_quest1","�ɹ�");
        if(blade=present("black blade",this_object()))
        {
                message_vision(HIR"���ʮ�������Ұ���۾�ͻȻ����������˫�ֽ����ʳ�������$N��
˫ϥ�����Ȼ�����㣬�ú����˵�����ת��������������������ˡ���\n"NOR,winner);
                blade->move(winner);
        }
                
} 
int accept_fight(object me)
{
        int count;
        object blade;
        
        if(!present("black blade",this_object())) return 0;
        if(me->query("���_quest1")=="�ɹ�")
        {
                message_vision(HIW"���ʮ�����ʵ������Ұ���������飬�����������𣿡�\n"NOR,me);
                return 0;
        }
        if(me->query("���_quest1")&&me->query("���_quest1")+600>time())
        {
                message_vision(HIR"���ʮ���ɲ�м�Ŀ���$N˵���������°ܽ���������������\n"NOR,me);
                return 0;
        }
   count=me->query_temp("���_��ս����");
        
        if(me->query("combat_exp")<2500000||me->query("score")<15000)
        {
        if(count==0)
                message_vision(HIY"���ʮ���ɻ�Ȼ����˫����ɨ��$Nһ�ۣ�΢̾һ������Ŀ���\n"NOR,me);
        
        else if(count==1)
                message_vision(HIY"���ʮ���ɺ���һ���ͺȵ������˶�����ʮ���ɣ���ս�������µµ��Ϊ֮����\n"NOR,me);
        else if(count==2)
        {
                message_vision(HIW"���ʮ����üͷ΢�壬��Ǻ����һ��������է�֡�\n"NOR,me);
                kill_ob(me);
                me->delete_temp("���_��ս����");
                return 2;
        }
        me->add_temp("���_��ս����",1);
        return 0;
        } 
        message_vision(HIY"���ʮ���ɻ�Ȼ����˫����Ŀ����綢��$N����������㣬���У�\n"NOR,me);
        return 1;
}
        
        
int accept_object(object who, object ob)
{
        if(!ob->query("saki")) return 0;
        message_vision(HIC"���ʮ����˫�ֽ�����ƿ��ƣ�����ر���\n"NOR,who);
        call_out("be_poisoned",5+random(5),who);
        return 1;
} 
int be_poisoned(object who)
{
    message_vision(HIR"\n���ʮ���ɲ�����������ƣ������ݺᣬһ��������\n
ͻȻ���ʮ���ɻ��������������죬��Ȼ�������ӣ��㡣���㡣��������
��λ"+RANK_D->query_respect(who)+"���������涾�������ܱƳ���Ҳ�ع������ϣ�����һ������
��֪��ɷ��Ӧ��\n"NOR,who);
        if(who->query("���_quest4")!="�ɹ�"){
                message_vision(HIR"\n˭֪�������䣬$N��ɫͻ�䣬һ����Ѫ���˳�����\n"NOR, this_object());
                die();
           return 1;
        }
    tell_object(who,HIY"���������򡡣���󣯣� \n"NOR);
        who->set_temp("answer_person",1);
        return 1;
} 
int do_answer(string arg)
{
        object skinmask,who;
        
        who=this_player();
        if(!who->query_temp("answer_person")) return 0;
        if(arg=="yes")
        {
                message_vision("$N��ɫ���صص���һ��ͷ��\n",who);
                message_vision(HIB"���ʮ���������Ц�����ã��ҽ���Լս����ԭһ��죬��ʹ���
һս�ɡ�����ص�ӿȪ�౨��\n"NOR,who);
                skinmask=new(__DIR__"obj/skinmask");
                skinmask->move(who);
                message_vision("���ʮ���ɸ�$Nһ��װ����\n",who);
                who->set("���_quest5","�ɹ�");
                who->delete_temp("answer_person");
                return 1;
                
        }
        if(arg=="no"){
                message_vision(HIR"���ʮ������ȻһЦ���³�����Ѫ�����ض�����\n"NOR,who);
        if(!who->query("imbue/tianfeng")){
                imbue_event(who);
        }
                die();
                return 1;
        }
        return 0;
} 
void recruiting(object ob)
{
        if(ob->query("���_quest6")=="ʧ��")
        {
                message_vision(HIR"���ʮ������ȻһЦ���³�����Ѫ�����ض�����\n"NOR,ob);
           this_object()->die();
                return;
        }
        if(ob->query("���_quest6")=="�ɹ�")
        {
                tell_object(ob,WHT"���ʮ��������������˫�ۣ�΢΢Ц�����ã���һ��������������ѧ�ˡ�\n"NOR);
                return;
        }
} 
void attempt_apprentice(object me)
{
    if(me->query("���_quest6")=="�ɹ�")
    {
        command("recruit " + me->query("id") );
        return;
    }
    else
        command("sigh"); 
} 
         
void recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "ninja");
} 
void imbue_event(object me){
    object obj, weapon, *inv;
    string prop;
    int i;
    
    if(!interactive(me) || environment(me) != environment(this_object())) {
            return;
    }
        obj = me->query_temp("weapon");
        if(objectp(obj) && obj->query("owner")) {
                weapon = me->query_temp("weapon");
        } else { 
                inv = all_inventory(me);        
                for(i=0; i<sizeof(inv); i++) {
                        if(inv[i]->query("weapon_prop") && inv[i]->query("owner")) {
                           weapon = inv[i];
                                break;
                        }
                }       
        }
        if(!objectp(weapon)){
                if(!objectp(obj)) {
                        message_vision(RED"\n������Ѫ�����˵���˲��������˰���ɫ�ĺۼ�������\n"NOR, me);
                } else {
                        message_vision(HIR"\n������Ѫ������$N��" + obj->name() + HIR"�ϣ���˳��"
                        + obj->name() + HIR"�䵽�˵��ϡ�\n"NOR, me);    
                }
        }else{
                message_vision(HIR"\n������Ѫ������$N��"NOR + weapon->name() + 
                                HIR"�ϣ�˲��������˰���ɫ�ĺۼ����� \n"NOR, me);
                if(weapon->query("weapon_prop")) {
                        prop="weapon_prop/";
                }
                if(weapon->query("equipped") == "wielded") {
                        weapon->unequip();
                }
        weapon->add(prop+"strength", 5);
        weapon->add(prop+"damage", 10);
                weapon->save();
                me->set("imbue/tianfeng", 1);
                me->save();
                return;
        }
        me->set("imbue/tianfeng", 2);
        me->save();
        return;
}  