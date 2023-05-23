#include "Model.h"
#include "User.h"
#include "mainwindow.h"

#include <QApplication>

#include <QtXml>
#include <QTextStream>

Model* readXmlFile(){
    QDomDocument modelXML;
    QFile xmlFile("XMLFile1.xml");
    if (!xmlFile.open(QIODevice::ReadOnly ))
    {
        throw std::runtime_error("file is not loaded");
    }


    modelXML.setContent(&xmlFile);

    xmlFile.close();

    QDomElement xmlRoot = modelXML.documentElement();
    QDomElement xmlNode = xmlRoot.toElement();

    std::map<ID_t, User*> users;
    std::map<ID_t, Node*> nodes;

    Model* model = new Model();
    Hierarchy* hierarchy = nullptr;

    qDebug() << xmlNode.tagName();

    {
        int modelId  = xmlNode.attribute("id").toInt();
        std::string name = xmlNode.attribute("name").toStdString();
        std::string comment = xmlNode.attribute("comment").toStdString();
        model = new Model(modelId,name,comment);
    }


    qDebug() << QString::fromStdString(model->getName()) << ' ' << QString::fromStdString(model->getComment());


    auto nodes_ = xmlNode.elementsByTagName("users");
    auto usersXml = xmlNode.elementsByTagName("users").at(0).toElement();
    auto hierarchyXml = xmlNode.elementsByTagName("hierarchy").at(0).toElement();
    auto judgmentsXml = xmlNode.elementsByTagName("judgments").at(0).toElement();
    auto alternativesXml = xmlNode.elementsByTagName("alternatives").at(0).toElement();

    // read users
    if(usersXml.isNull() == false){
        auto userNodes = usersXml.elementsByTagName("user");

        for(int userElementIndex = 0; userElementIndex < userNodes.length(); userElementIndex ++){
            auto userElement = userNodes.at(userElementIndex).toElement();

            ID_t id = userElement.attribute("id").toInt();
            std::string name = userElement.attribute("name").toStdString();
            std::string comment = userElement.attribute("comment").toStdString();

            User* newUser = new User(id,name,comment);
            users[newUser->getId()] = newUser;
        }
    }

    // read hierarchy
    if(hierarchyXml.isNull() == false){
        hierarchy = new Hierarchy();
        hierarchy->setName(hierarchyXml.attribute("name").toStdString());

        auto nodeElements = hierarchyXml.firstChild().toElement().elementsByTagName("node");

        std::map<ID_t, ID_t> nodeParentMap;
        ID_t rootNodeId;

        for(int nodeElementIndex = 0; nodeElementIndex < nodeElements.length(); nodeElementIndex++){
            auto nodeElement = nodeElements.at(nodeElementIndex).toElement();
            ID_t id = nodeElement.attribute("id").toInt();
            std::string name = nodeElement.attribute("name").toStdString();
            std::string comment = nodeElement.attribute("comment").toStdString();
            if(nodeElement.hasAttribute("parentId")){
                ID_t parentId = nodeElement.attribute("parentId").toInt();
                nodeParentMap.insert({id, parentId});
            }else{
                rootNodeId = id;
            }
            Node* newNode = new Node(id);
            newNode->setHierarchy(hierarchy);
            newNode->setName(name);
            newNode->setComment(comment);


            nodes[id] = newNode;
        }

        for(auto& node_parent: nodeParentMap){
            nodes[node_parent.first]->setParent(nodes[node_parent.second]);
            nodes[node_parent.second]->addChild(nodes[node_parent.first]);
        }

        hierarchy->setNodes(nodes);
        hierarchy->setRoot(rootNodeId);
    }


    // read judgments
    if(judgmentsXml.isNull() == false){
        auto usersJudgments = judgmentsXml.elementsByTagName("userJudgments");
        for(int judgmentsIndex = 0; judgmentsIndex < usersJudgments.length(); judgmentsIndex ++){
            auto userJudgmentsElement = usersJudgments.at(judgmentsIndex).toElement();
            ID_t userId = userJudgmentsElement.attribute("userId").toInt();

            auto userJudgments = userJudgmentsElement.elementsByTagName("judgment");


            for(int judgmentIndex = 0; judgmentIndex < userJudgments.length(); judgmentIndex++){
                auto judgmentElement = userJudgments.at(judgmentIndex).toElement();
                ID_t parentNodeId = judgmentElement.attribute("parentNodeId").toInt();
                ID_t firstNodeId = judgmentElement.attribute("firstNodeId").toInt();
                ID_t secondNodeId = judgmentElement.attribute("secondNodeId").toInt();
                double value = judgmentElement.attribute("parentNodeId").toDouble();
                std::string comment  = judgmentElement.attribute("comment").toStdString();

                PairwiseJudgment judgment;
                judgment.setFirstNodeId(firstNodeId);
                judgment.setSecondNodeId(secondNodeId);
                judgment.setValue(value);
                judgment.setComment(comment);
                judgment.setUserId(userId);


                Node* parentNode = hierarchy->getNodeByID(parentNodeId);
                auto& nodeJudgments =  parentNode->getJudgments().getJudgments();


                nodeJudgments[userId].push_back(judgment);
            }
        }
    }



    // read alternatives
    if(alternativesXml.isNull() == false){
        auto alternativesElements = alternativesXml.elementsByTagName("alternative");

        for(int alternativeIndex = 0; alternativeIndex < alternativesElements.length(); alternativeIndex++){
            auto alternativeElement = alternativesElements.at(alternativeIndex).toElement();
            std::string name = alternativeElement.attribute("name").toStdString();
            ID_t id = alternativeElement.attribute("id").toInt();
            std::string comment = alternativeElement.attribute("comment").toStdString();

            Alternative alternative;
            alternative.setId(id);
            alternative.setComment(comment);
            alternative.setName(name);

            model->addElternative(alternative);
        }
    }

    model->setHierarchy(hierarchy);
    model->setUsers(users);

    return model;
}

void saveXmlFile(){

}

int main(int argc, char *argv[])
{
    Model* model = readXmlFile();


    QApplication a(argc, argv);
    MainWindow w;

    w.setModel(model);
    w.show();



    return a.exec();
}
