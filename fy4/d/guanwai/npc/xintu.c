 inherit NPC;
void create()
{
        set_name("����", ({ "xintu"}) );
        set("gender", "����" );
        set("age", 55);
        set("str", 10);
        set("long", @LONG
һ��װ���������Ѻ��ƾɵĲ��ˣ�������������ͽ��
LONG
);
        set("attitude", "peaceful");
        set("title", "��ʥ��ͽ");
        set("combat_exp", 10000);
        set_skill("unarmed", 70);
        set_skill("bloodystrike", random(50)+10);
        set_skill("force", 50);
        map_skill("unarmed", "bloodystrike");
    set_skill("iron-cloth", random(50)+100);
        set("chat_chance", 20);
        set("chat_msg", ({
                (: random_move :),
                "\n�������򲼴�����������һ�ݣ��岽һߵ��ִ�Ŷ���ʥ����ǰ�����š�\n",
        }) ); 
        setup();
        carry_object(__DIR__"obj/hada")->wear();
 
}  