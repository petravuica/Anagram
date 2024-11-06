#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AnagramGroup{
    char** words;
    int count;
    int capacity;
}AnagramGroup;

typedef struct AnagramGroups{
    AnagramGroup** groups;
    int count;
    int capacity;
}AnagramGroups;
void sortString(char* str){
    int n = strlen(str);
    int i, j;
    for(i=0;i<n-1;i++){
        for(j=0;j<n-1-i;j++){
            if(str[j]>str[j+1]){
                char temp = str[j];
                str[j]=str[j+1];
                str[j+1]=temp;
            }
        }

    }
}
AnagramGroups* createAnagramGroups(){
    AnagramGroups* groups = (AnagramGroups*)malloc(sizeof(AnagramGroups));
    groups->count=0;
    groups->capacity=2;
    groups->groups=(AnagramGroup**)malloc(groups->capacity*sizeof(AnagramGroup*));
    return groups;
}
void addGroupToGroups(AnagramGroups* groups, AnagramGroup* group){
    if(groups->count == groups->capacity){
        groups->capacity *=2;
        groups->groups = (AnagramGroup**)realloc(groups->groups, groups->capacity * sizeof(AnagramGroup*));
    }
    groups->groups[groups->count] = group;
    groups->count++;
}

AnagramGroup* createAnagramGroup(){
    AnagramGroup* group = (AnagramGroup*)malloc(sizeof(AnagramGroup));
    group->count = 0;
    group->capacity = 2;
    group->words = (char**)malloc(group->capacity*sizeof(char*));
    return group;
}
void addWordToGroup(AnagramGroup* group, const char* word){
    if(group->count == group->capacity){
        group->capacity *= 2;
        group->words = (char**)realloc(group->words, group->capacity*sizeof(char*));
    }
    group->words[group->count] = strdup(word);
    group->count++;
}
void freeAnagramGroup(AnagramGroup* group) {
    for (int i = 0; i < group->count; i++) {
        free(group->words[i]);
    }
    free(group->words);
    free(group);
}
void freeAnagramGroups(AnagramGroups* groups) {
    for (int i = 0; i < groups->count; i++) {
        freeAnagramGroup(groups->groups[i]);
    }
    free(groups->groups);
    free(groups);
}
AnagramGroups* anagramCreator(char** words, int numWords){

    AnagramGroups* result = createAnagramGroups();

    for(int i = 0;i<numWords;i++){
        char sortedWord[100];
        strcpy(sortedWord, words[i]);
        sortString(sortedWord);

        int foundGroup = 0;
        //printf("%d \n ", result->count);
        for(int j = 0;j<result->count;j++){
            char firstWord[100];
            strcpy(firstWord, result->groups[j]->words[0]);
            sortString(firstWord);

            if(strcmp(sortedWord, firstWord) == 0){
                addWordToGroup(result->groups[j], words[i]);
                foundGroup=1;
                break;
            }
        }
        if(!foundGroup){
            AnagramGroup* newGroup = createAnagramGroup();
            addWordToGroup(newGroup, words[i]);
            addGroupToGroups(result, newGroup);
        }
    }

    return result;
}
void printAnagramGroups(AnagramGroups* groups) {
    for (int i = 0; i < groups->count; i++) {
        printf("Grupa %d: ", i + 1);
        for (int j = 0; j < groups->groups[i]->count; j++) {
            printf("%s ", groups->groups[i]->words[j]);
        }
        printf("\n");
    }
}
int main(){
    char* words[] = {"pero", "created", "reacted", "epro", "karla", "krasanjeodmor", "jadranskomore", "list", "stil", "ilst"};
    int numWords = sizeof(words)/sizeof(words[0]);
    AnagramGroups* groups = anagramCreator(words, numWords);
    printf("%d\t %d\n", sizeof(words), sizeof(words[0]));

    printAnagramGroups(groups);

    freeAnagramGroups(groups);


    return 0;
}
