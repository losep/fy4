inherit NPC;
inherit F_MASTER;
int leave();
#include <ansi.h> 
void create()
{
    set_name("������", ({ "hua zhenzhen", "zhenzhen", "hua"}) );
    set("gender", "Ů��" );
    set("age", 18);
    set("int", 30);
    set("per", 30);
    set("reward_npc", 1);
    set("difficulty", 30);
    set("class","huashan");
    set("apprentice_available", 50);
    create_family("��ɽ��", 15, "����");
    set("title", "��ɽ�� ��ʮ�ߴ�����");
        set("rank_nogen",1);
    set("long",
        "��˹˹���ģ�����������ʼ�յʹ���ͷ���·��߼����ˡ� 
żȻ̧ͷʱ��һ˫�������ǹ������������ȴ�ֳ�΢΢�κ졣 \n"
        );
    set("inquiry", ([
                        "leave" : (: leave :),
        ]));
    
    
    set("no_busy",10);
    switch (random(3)) {
                case 0: set("resistance/kee",30);
                        break;
                case 1: set("resistance/gin",30);
                        break;
                default: set("resistance/sen",30);
                }
    
    set("force", 8000);
    set("max_force", 8000);
    set("force_factor",160);
    set("str", 40);
    
    set("score", 5000);
    set("combat_exp", 9999999); 
    set_skill("unarmed",160);
    set_skill("sword", 200);
    set_skill("force", 200);
    set_skill("hanmei-force", 200);
    set_skill("anxiang-steps", 180);
    set_skill("cloud-dance", 200);
    set_skill("move", 180);
    set_skill("literate", 140);
    set_skill("dodge", 160);
        set_skill("perception", 100);
    set_skill("parry", 160);
    set_skill("throwing", 200);
    set_skill("iron-cloth", 180);
    set_skill("spring-water", 120);
    set_skill("qingfeng-sword", 170);
    set_skill("tanzhi-shentong", 160);
    set_skill("zhaixin-claw",100);
    
    map_skill("unarmed", "zhaixin-claw");
    map_skill("force", "hanmei-force");
    map_skill("dodge", "cloud-dance");
    map_skill("sword", "qingfeng-sword");
    map_skill("parry", "qingfeng-sword");
    map_skill("move", "anxiang-steps");
    map_skill("iron-cloth", "spring-water");
    map_skill("throwing", "tanzhi-shentong");
    
    
    set("ranks",({"����","С��","����","����","����",WHT"����"NOR,WHT"��ʥ"NOR,HIW"����"NOR}));
    setup();
    carry_object(__DIR__"obj/ycloth")->wear();
    carry_object(__DIR__"obj/qingfeng")->wield();
}
void reset()
{
        delete_temp("learned");
        set("apprentice_available", 1);
}
void attempt_apprentice(object ob)
{
        if( query("apprentice_available") ) {
                if( find_call_out("do_recruit") != -1 )
                        command("say ������һ��һ������");
                else
                        call_out("do_recruit", 2, ob);
        } 
}
void do_recruit(object ob)
{
        if((string)ob->query("gender") == "Ů��" 
                        &&(int)ob->query("combat_exp")>1200000&&ob->query("class")=="huashan"){      
                if (ob->query("marks/�ҳ�")==1 
                        || (ob->query("marks/�ҳ�")== -1 && ob->query("marks/kill_kumei"))
                        ){
                        message_vision("$N����$n����һ�����̾�˿���˵����Ҳ�������һ�죬���ܷ�����ɽ�ɡ��� \n",
                                this_object(), ob);
                        command("recruit " + ob->query("id") );
                        message_vision("\n$Nת���ߵ����ڱߣ�������$nʾ���������\n", this_object(),ob); 
                        message_vision("$N��Ӱһ�Σ���Ȼ�Ӿ��ڱ���ʧ�ˡ�\n", this_object());
                        environment(ob)->go_cliff(ob);
                        destruct(this_object());
                }
                else if (ob->query("marks/�ҳ�")== -1 && !ob->query("marks/kill_kumei")) {
                        message_vision("$N����$n����һ�����̾�˿���˵����Ҳ��������ʵ�Ļ�ɽ���ӣ�\nҪ֪���������е���Щ�������˵İ��಻��������ɽ�ɾ���Զ���ܷ����󡣡� \n",
                                this_object(), ob);            
                        command("wave");
                        message_vision("\n\n$N��Ӱһ�Σ���Ȼ�Ӿ��ڱ���ʧ�ˡ�\n", this_object());
                        destruct(this_object());
                }
                
                else {
                        message_vision("$N̾�˿���˵������ɽ���ڶ���֮�ʦ�øö�Ϊʦ�ų��������� \n",
                                this_object());
                        command("wave");
                        message_vision("\n\n$N��Ӱһ�Σ���Ȼ�Ӿ��ڱ���ʧ�ˡ�\n", this_object());
                        destruct(this_object()); 
           }
                
        } 
        else {
                message_vision("��Ȼ�Ǻڰ���ҹɫ�£�$N���ǲ�����˼�ص���ͷ��С��˵���� �Ҳ���\n", this_object());
                message_vision("��û�����ĵ��ӣ���ô�������˵�ʦ���أ��� \n", this_object());
                message_vision("$N��Ӱһ������ʧ��ҹĻ�С�\n", this_object()); 
                destruct(this_object());
        } 
}
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "huashan");
        add("apprentice_availavble", -1);
} 
void init(){
        ::init();
        call_out("do_leave", 30);
        add_action("do_killing", "kill");
} 
void do_leave(){
        if( find_call_out("do_recruit") != -1 ) {
                call_out("do_leave", 5);
        }
        environment(this_object())->do_leave();
} 
int do_killing(string arg)
{
    object player, victim;
    string id,id_class;
    player = this_player();
    if(!arg || arg == "") return 0;
    victim = present(arg, environment(player));
        if(!objectp(victim))
                return notify_fail("����û������ˡ�\n");
    if(living(victim))
    {
        id_class=victim->query("class");
        id=victim->query("id");
           if(id_class == "huashan"&& userp(victim)&& player!= victim)
        {
            message_vision(HIW
"$N̾�˿�����ɱ���ߣ���ɱ֮��\n"NOR, this_object());
            this_object()->kill_ob(player);
            player->kill_ob(this_object());
            player->start_busy(2);
            return 0;
        } 
    }
    return 0;
} 
int leave() {
        if (this_player()->query("class")!="huashan") return 0;
        message_vision(CYN"$N����ͷ˵�����ðɡ�\n"NOR, this_object());
        message_vision(CYN"$N˵��ֻ�ǻ�ɽ�Ź�ɭ�ϣ���ˮ������ժ�ĵ��ؾ����ܴ��ߡ�\n"NOR,this_object());
        return 1;
}     