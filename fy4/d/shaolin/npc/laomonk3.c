 // teacher.c
inherit NPC;
#include <ansi.h>
void restrict_move(); 
void create()
{
        string *name = ({"ɨ�ص�","�ֻ���","�Ͳ˵�"});
//      set_name(name[random(sizeof(name))]+"�Ϻ���", ({ "old monk", "monk"}) );
        set_name("�ֻ����Ϻ���", ({ "old monk", "monk" }) );
        set("nickname",HIW"һ����Ⱦ"NOR);
        set("gender", "����" );
        set("age", 62);
        set("vendetta_mark","shaolin");
        set("int", 30);
        set("cor",30);
        set("cps",60);
        
        set("resistance/kee",40);
        set("resistance/gin",40);
        set("resistance/sen",40); 
        set("str",40+random(20));
        set("class","shaolin");
        set("pursuer", 1);
        set("long",
                "�����������ɨ��������ɮ����˵��������ز�¶�ĸ��֡�\n"
                );
       set("chat_chance", 1);
        set("chat_msg", ({
                (: restrict_move :)
         }) ); 
        set("attitude", "peaceful");
        set_skill("move", 200);
        set_skill("dodge", 140);
        set_skill("force", 140);
        set_skill("unarmed",140);
        set_skill("puti-steps",140);
        set_skill("dabei-strike",140);
        set_skill("xiaochengforce",140);
        set_skill("yiyangzhi",140);
        set_skill("iron-cloth",100);
           set_skill("yijinjing",100);
        map_skill("iron-cloth","yijinjing");
        map_skill("dodge", "puti-steps");
        map_skill("force", "xiaochengforce");
        map_skill("unarmed", "yiyangzhi");
        set("chat_chance_combat", 30);
        set("chat_msg_combat", ({
          (: perform_action, "unarmed.qiankun" :)
            }) );
        
        set("combat_exp", 4000000);
        setup();
        carry_object("/obj/armor/cloth")->wear();
        carry_object(__DIR__"obj/ironfist")->wield();
        carry_object(__DIR__"obj/ironfist")->wield();
}  
restrict_move() {
            string where;
            where=file_name(environment(this_object()));
            if (where[0..9]=="/d/shaolin") {
                        this_object()->random_move();
                        }
                else {  message_vision(YEL"�Ϻ��п��˿����ܣ�һ�ﲻ�����뿪�ˡ�\n"NOR,this_object());
                        this_object()->move("/d/shaolin/heshang");
                }
           }          