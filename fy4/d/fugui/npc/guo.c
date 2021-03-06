#include <ansi.h>
inherit NPC; 
void create()
{
        set_name("郭大路", ({ "guo", "guo dalu" }) );
        set("long",
                "郭大路，大方的大，上路的路。人如其名，郭大路是个很大路的人。\n");
        set("attitude", "heroism");
        create_family("富贵山庄",7,"大侠");
        set("reward_npc", 1);
        set("difficulty", 5);
        if (random(3)) set("attitude","friendly");
        set("str",40);
        set("cor",50);
        set("cps",25);
        set("agi",40);
        set("int",40);
        set("per",20);
        set("tol",30);
        set("skill_public",1);
        set("max_force",1200);
        set("force",1200);
        set("force_factor",70);
        
        set("resistance/kee",40);
        set("resistance/gin",40);
        set("resistance/sen",40);
                
        set("m_success/结拜郭大路",1);
        set("chat_chance",1);
        set("chat_msg", ({
                        "郭大路说道：“我这人难道是天生的穷命？就不能有天不挨饿的？\n哎，现在连早上吃的鸭皮怕都已经消化得快差不多了。”\n",
                                })  );
        
        set("combat_exp", 4000000);
        
        set_skill("unarmed", 140);
        set_skill("force",180);
        set_skill("parry", 140);
        set_skill("move",140);
   set_skill("yue-strike",180);
        set_skill("iron-cloth",150);
        set_skill("skyforce",100);
        set_skill("literate",140);
        set_skill("perception",140);
        
        map_skill("unarmed","yue-strike");
        map_skill("force","skyforce");
        
        set("inquiry",  ([
                "王动" : "他是我郭大路的好兄弟,可是我....唉,对不住他....\n",
                "林太平" : "他是我郭大路的好兄弟,可是我....唉,对不住他....\n",
                "燕七" : "他是我郭大路的好兄弟,可是我....唉,对不住他....\n",
                "烧鸭" : "麦老广这糟老头子的烧鸭实在不错,实在不错.\n",
                "wangdong" : "他是我郭大路的好兄弟,可是我....唉,对不住他....\n",
                "lintaiping" : "他是我郭大路的好兄弟,可是我....唉,对不住他....\n",
                "yanqin" : "他是我郭大路的好兄弟,可是我....唉,对不住他....\n",
                "kaoya" : "麦老广这糟老头子的烧鸭实在不错,实在不错.\n",
                ]));
        setup();
        carry_object("/obj/armor/cloth")->wear();
} 
void init()
{
        ::init();
       add_action("do_jiebai","jiebai");
} 
void attempt_apprentice(object me)
{
        command("shake");
        command("say 现在我心烦意乱，那有闲心收徒？\n");
} 
int accept_object(object who, object ob)
{       
        object jinlian;
        
        if (ob->query("name")=="绍兴女儿红" && ob->query("liquid/name")=="绍兴女儿红"&& ob->query("liquid/remaining")>100)
        {
                command("shake " + who->query("id"));
                command("say 这也叫酒吗？入口不醇，淡而无味，不过瘾，不过瘾！\n");
           who->set_temp("marks/女儿红",1);
                return 1;
        }
        
        if (ob->query("name")=="烂瓦罐" && ob->query("liquid/name")=="极品女儿红" && ob->query("liquid/remaining")>100)
        {
                write("郭大路拍碎烂瓦罐的泥盖，将酒倒入口中，眯缝着眼睛，面上露出陶\n醉的神情。良久，郭大路长舒一口气：“人间极品，人间极品啊！”\n");
                if (who->query_temp("marks/女儿红"))
                {
                        who->set_temp("marks/烂瓦罐",1);
                        return 1;
                }
                else
                {
                        command("hmm");
                }
                return 1;
        }
        
        if (ob->query("name")=="烤鸭")
        { 
                who->set_temp("marks/烤鸭",1);
                write("郭大路一下窜了起来大叫道：“啊，麦老广的烧鸭，老兄真是上路啊，\n不过么，空有肥鸭，没有美酒又怎让人下咽呀。\n");
                return 1;
        }
        
        if (ob->query("name")==HIG"酒坛"NOR && ob->query("liquid/name")=="竹叶青" && ob->query("liquid/remaining")==1500 )
        {
                if (who->query_temp("marks/烤鸭"))
                {
                        write("郭大路拍碎封坛的泥盖，闭着眼睛，深深吸了口气，叹道：“这不是\n香气，简直是仙气啊。”\n");
                        command("pat " + who->query("id"));
                        write("郭大路大笑道：“兄弟比我郭大路还要上路啊，这条金链子麻烦你交\n给我大哥王动，说郭大路现在想想还是回山庄的好，不仅有饭吃有酒\n喝，还有他们几个好朋友，再赶我走我也不走了。\n");
                        who->start_busy(3);
                        jinlian = new(__DIR__"obj/chain");
                        jinlian->move(who);
                        who->set_temp("marks/得到金链",1);
                        who->delete_temp("marks/烤鸭");
                        call_out("goback", 3);
                        return 1;
                   }
                else 
                {
                        write("郭大路顿时两眼放光，一饮而尽后，舔舔舌头晃晃脑袋说，这酒么，\n好则好矣，但味走偏锋，失之醇厚，不过瘾，不过瘾！\n");
                }
        return 1;
        }
        
        message_vision("$N扫了一眼$n手中的东西，懒懒的说，“吃这种东西，还不如饿死算了。”\n",this_object(),this_player());
        return 0;
} 
int goback()
{
        write("郭大路两眼放光，风卷残云般扫光面前的肥鸭美酒，舔舔舌头晃晃脑\n袋,一副意犹未尽的样子。\n\n");
        say ("郭大路说道：“酒足饭饱，出去走走，顺便打听一下兄弟们的消息。”\n");
        say ("郭大路话声方了，便已匆匆走出破庙，不知所踪。\n\n");
        destruct( this_object());
        return 1;
} 
int recognize_apprentice(object ob)
{
        if( !ob->query("m_success/结拜郭大路") ){
                command("say 我这点功夫，哪里敢提什么指导，你还是另找高人吧！\n");
                return 0;
        }
        return 1;
} 
int do_jiebai(string arg)
{
        string guo;
        object me,ob; 
        me = this_player();
        ob = this_object();
        
        if( !arg
        ||      sscanf(arg, "with %s",guo)!=1
        ||      !me)
                return notify_fail("指令格式: jiebai with <某人>\n");
                
        if( me->query("m_success/结拜郭大路"))  
   {
                message_vision("$N恭恭敬敬地向$n拱手请安，叫道：「大路兄弟！」\n", me, ob);
                return 1;
        } 
        if(me->query_temp("marks/烂瓦罐") && me->query("marks/救济劫匪"))
        {
/*              if(time()-(int) me->query("last_time_jiebai_guo") < 1800){
                message_vision("$N笑道：你怎么这么快又回来了．．．让我考虑考虑再说嘛！\n",ob);
                return 1;
        }
            if ( random(10) ){
                        message_vision("$N咳了两声，说道：我得考虑考虑再决定。\n",this_object());
                        me->set("last_time_jiebai_guo",time());
                        return 1;
        } 
*/
        message_vision(HIG"$N大笑：好好，我又多了个兄弟。现今江湖之上颇为流行小重山掌，可惜
无人悟出其中秘诀，为兄当年大醉之下领悟到小重山掌秘诀，可于你分享。\n"NOR,
                        this_object());
                tell_object(me, HIY"\n郭大路在你耳边如此这般说了一通，你不由得恍然大悟。\n"NOR);
                message("vision", "\n郭大路在"+me->name()+"耳边密语几句，"+me->name()+"不由得连连点头。\n",
                                environment(me), me); 
                me->set("m_success/结拜郭大路",1);
                me->add("score",1000);
                return 1;
 
        } else {
                command("hmm");
                message_vision("$N摇摇头：我$N又穷又懒，与我结拜会连累你的。\n",this_object());
        }
    return 1;
}      
