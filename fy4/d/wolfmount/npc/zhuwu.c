 inherit NPC;
inherit F_MASTER;
#include <ansi.h> 
void create()
{
        set_name("朱五太爷", ({ "master zhuwu", "master", "zhuwu" }) );
        set("gender", "男性" );
        set("age", 75);
        set("agi", 35);
        set("int", 40);
        set("spi", 25);
        set("cor", 20);
        set("con", 20);
        set("per", 40);
        set("str", 100);
        set("attitude","heroism");
        set("apprentice_available", 5);
        set("long",
                "他全身都已冰冷僵硬，脸上的肌肉也已因萎缩而扭曲．一张本来很庄\n严的脸，已变得说不出的邪恶可怖。\n"
                );
        create_family("狼山", 3, "山主");
        set("rank_nogen",1); 
        set("ranks",({ "小喽罗","大喽罗","小头目","大头目","大头领",RED"大盗"NOR,RED"盗帅"NOR,HIR"副山主"NOR }));
        set("force_factor",400);
        set_temp("apply/damage",300);
        set("max_force", 10000);
        set("force", 10000);
        set("attitude", "peaceful");
        
        set_skill("hammer", 200);
        set_skill("assasin-hammer", 180);
        set_skill("animal-training", 200);
        set_skill("cursism", 200);
        set_skill("force", 180);
        set_skill("move", 150);
        set_skill("wolf-force",170);
        set_skill("wolf-curse",100);
        set_skill("parry", 200);
        set_skill("dodge", 150);
        set_skill("xueyeqianzong", 150);
   set_skill("literate", 140);
        set_skill("unarmed", 200);
        set_skill("wolf-strike", 180);
        set_skill("dagger",200);
        set_skill("summonwolf", 200);
        set_skill("xinyue-dagger",120);
        set_skill("perception", 100);
        map_skill("dodge","xueyeqianzong");
        map_skill("dagger","xinyue-dagger");
        map_skill("unarmed","wolf-strike");
        map_skill("parry","assasin-hammer");
        map_skill("hammer","assasin-hammer");
        map_skill("force","wolf-force");
        map_skill("cursism","wolf-curse");
        set("combat_exp", 20000000);
        setup();
        carry_object(__DIR__"obj/graycloth")->wear();
        carry_object(__DIR__"obj/juque");
        carry_object(__DIR__"obj/rockhammer")->wield();
} 
int is_ghost()
{ 
        return 1; 
} 
void init(){    
        
        ::init();
        add_action("do_kill","kill");
        if(this_player()->query("title") == "狼山 "+HIR"蚩尤传人"NOR){
                call_out("chiyou", 1, this_player());
        }
} 
void chiyou(object me){
        object ob;
        if(!interactive(me) || environment(me) != environment(this_object())){
                return;
        }
        message_vision(HIR"$N悲啸一声：你这不世邪魔的传人！纳命来！\n"NOR, this_object());
        this_object()->kill_ob(me);
        if(ob=present("wanyan tie", environment(this_object()))){
           ob->kill_ob(me);
        } else if(ob=present("wanyan gang", environment(this_object()))){
                ob->kill_ob(me);
        }
        return;
} 
int do_kill(string arg)
{
        object me,ob;
        object player, victim;
        string id,id_class;
        me = this_player();
        if(arg == "master zhuwu" || arg == "master" )
        {
                if ( ob=present("wanyan tie",environment(this_object())) )
                {
                        message_vision("$N对$n大喝一声：＂你不够斤两跟我主动手，让我先宰了你！\n",ob,me);
                        ob->kill_ob(me);
                        return 1;
                }
                else if ( ob=present("wanyan gang",environment(this_object())) )
                {
                        message_vision("$N对$n大喝一声：＂你不够斤两跟我主动手，让我先宰了你！\n",ob,me);
                        ob->kill_ob(me);
                        return 1;
                }
                else 
                {
                        return 0;
                }
        }
        player = this_player();
        if(!arg || arg == "") return 0;
        victim = present(arg, environment(player));
        if(!objectp(victim))
                return notify_fail("这里没有这个人。\n");
        if(living(victim))
        {
                id_class=victim->query("class");
                id=victim->query("id");
                   if(id_class == "wolfmount"&& userp(victim)&&player!=victim)
                {
                        message_vision(HIW"$N对$n喝道：狼山子弟,同气连枝,不容外人欺侮！\n"NOR, this_object(),player);
                        this_object()->kill_ob(player);
                        player->kill_ob(this_object());
                        if (!player->is_busy()) player->start_busy(2);
                        return 0;
                } 
        }
        return 0;
} 
void reset()
{
                set("apprentice_available", 5);
} 
void attempt_apprentice(object ob)
{
        if( query("apprentice_available") ) 
        {
                if( find_call_out("do_recruit") != -1 )
                        command("say 慢著，一个一个来。");
                else
                        call_out("do_recruit", 2, ob);
        } 
        else 
        {
                command("say 狼山弟子，贵精不贵多，不能再收了。");
        }
} 
void do_recruit(object me){
        if(me->query("title") == "狼山 "+HIR"蚩尤传人"NOR){
                return;
        }
        if( (string)me->query("class") != "wolfmount" )
        {
            command("say 我只收狼山子弟，你还是另谋高就吧！\n");
        }
        else if(!me->query("m_success/狼山灭奸"))
        {
                switch ( random(2) )
           {
                        case 0:
                                command("say 狼山已落入他人之手，我如何收你？\n");
                                me->set_temp("marks/拜朱五太爷",1);
                                break;
                        case 1:
                                me->set_temp("marks/拜朱五太爷",1);
                                command("say 我冤魂不灭，就是等着有人为我抱了仇，再传他一身武功。\n");
                                break;
                }
        } else  {
                if (me->query("combat_exp")<1200000) {
                        command("say 好，好，好娃子，再练几年再来找我。\n");
                        return;
                }
                command("say 你帮我报了大仇，我就收你为徒吧！\n");
                command("recruit " + me->query("id") );
        }
}
                
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "wolfmount");
        add("apprentice_availavble", -1);
}      
