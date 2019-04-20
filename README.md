# Holum

![Holum](Resource%20Files/Other/holum.png)

### Obiettivi del progetto
Holum è un progetto che focalizza i suoi obiettivi su usabilità, intuitività ed efficienza. 
È progettato per utenti di ogni età e possiede una varietà di caratteristiche che possono essere utilizzate per soddisfare una vasta gamma di interessi ed esigenze.
Si rivolge sia a utenti non specializzati o solo in parte avvertiti delle attività di programmazione informatica, sia a vari tipi di utenti specializzati, senza precludere nessuna tipologia.

L’obiettivo primario è quindi quello di sviluppare un software in grado di offrire varie funzionalità, tra cui la possibilità di **riproduzione multimediale** di filmati, sia pre-caricati appositamente dagli sviluppatori, che tramite la scelta dell’utente.
Inoltre, l’utilizzatore potrà caricare e visualizzare **modelli tridimensionali**, con la possibilità di ingrandire, ruotare e traslare il modello in questione, tramite alcuni sistemi di interazione. 
Un’altra funzionalità riguarda la creazione di un insieme di **videogiochi**, realizzati con lo scopo di intrattenimento e svago dell’utente. 

Ogni funzionalità del programma dovrà essere personalizzabile tramite la selezione di impostazioni adeguate alle preferenze e alle esigenze dell’utente. 
L’insieme di questi sottoprogrammi verrà poi raccolto e reso accessibile in un apposito **menù**.

L’interazione con il software dovrà avvenire tramite alcuni dispositivi in grado di raccogliere informazioni sulle scelte dell’utente, per poi tradurle in un linguaggio comprensibile dal calcolatore. 
Queste informazioni verrano quindi utilizzate per navigare all’interno del menù e del programma in generale.

Il software avrà anche il principale compito di suddividere l’immagine da visualizzare in 4 “parti” uguali, a due a due simmetriche e speculari.
Il software dovrà poi essere accompagnato da un’appropriato **sistema piramidale**, sostenuto da una struttura di supporto. 
Questa struttura dovrà sorreggere un monitor, il quale si occuperà di visualizzare l’immagine prodotta dal software.
Infine, la superficie riflettente della piramide, assieme alla suddivisione dell’immagine da visualizzare, dovrà creare il desiderato **effetto di tridimensionalità e profondità della proiezione nello spazio**.

### Specifiche tecniche
L’effetto utilizzato per la riproduzione delle immagini è conosciuto come **“Pepper’s Ghost”**, ovvero il “Fantasma di Pepper”: una tecnica illusoria utilizzata in teatro e in vari trucchi magici che consiste nell’utilizzo di una o più lastre di vetro, posizionate ad un angolo di 45˚ tra lo spettatore e la scena, unite a una particolare illuminazione, per dare l’illusione della rappresentazione nello spazio delle immagini proiettate.
Il contenuto che verrà proiettato sarà riprodotto da un software appositamente programmato, utilizzando il linguaggio C++ e le librerie **SFML, sfeMovie, OpenGL, assimp** e altre.

L'utente può quindi, come accennato sopra, interagire con il programma in diversi modi:
* **Utility Android**, sviluppata in Java, attualmente strutturata per la sola navigazione all’interno del software su PC, tramite connessione bluetooth;
* **Myo Armband** (https://www.myo.com), un braccialetto “smart” che tramite la la lettura dei movimenti muscolari permette il controllo wireless del software, utilizzando appositi gesti e movimenti. 
Per realizzare il collegamento con il programma in C++ abbiamo utilizzato la libreria myo, personalizzandone alcune funzioni per adattarla alle nostre esigenze;
* **Leap Motion** (https://www.leapmotion.com), un dispositivo in grado di rilevare accuratamente il movimento di dita e mani dell’utente nello spazio sovrastante al dispositivo stesso, permettendo l’interazione con il software in C++ tramite l’apposito SDK offerto da Leap Motion. 

Il programma offrirà la riproduzione di una serie di mini-giochi, pensati opportunamente per sfruttare al meglio le potenzialità dei dispositivi in questione.
Tramite questi controller è quindi possibile spostarsi all'interno dei menù e del programma, il quale offre varie categorie di intrattenimento. 

La schermata iniziale, successiva allo splash screen di benvenuto, presenta il menù, suddiviso nelle seguenti sezioni:
* **Video**: Archivio di filmati pensati appositamente per la rappresentazione nella piramide. 
I video pre-caricati sono caratterizzati da uno sfondo nero e da una riproduzione tridimensionale dei caratteri raffigurati, per garantirne l’ottimale visualizzazione e favorire l’illusione della raffigurazione di un simil-ologramma;
* **Games**: Sezione dedicata ai giochi, sia inerenti al Leap Motion che non. 
I giochi presenti potranno essere selezionati dall’utente tramite un menù, simile a quello principale;
* **3D**: Sezione dedicata al caricamento e alla rappresentazione di un archivio di modelli 3D in formato OBJ, tramite le funzionalità offerte da OpenGL. 
L’utente potrà interagire con il modello tramite un controller a sua scelta;
* **Settings**: Gestione delle preferenze utente riguardanti l’interfaccia grafica, audio e dei controller.
