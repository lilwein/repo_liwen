# esercitazione7

Questa esercitazione ha lo scopo di introdurvi alla libreria Pytorch e di farvi iniziare a lavorare 
con i multilayar perceptrons, a.k.a. fully connected networks. 

L'esercitazione è composta di tre parti:

1. [Introduzione a pytorch](Introduction_to_PyTorch.ipynb): questo jupyter notebook è una modifica di 
[quello creato da Phillip Lippe](https://uvadlc-notebooks.readthedocs.io/en/latest/tutorial_notebooks/tutorial2/Introduction_to_PyTorch.html) per il corso di Deep Learning dell'università di Amsterdam.
Questo notebook vi aiuterà a comprendere i concetti di base della libreria, non saltatelo.
2. [Introduzione alle reti neurali](Introduction_to_NeuralNetworks_using_PyTorch.ipynb): In questo notebook 
   implementerete un multilayer perceptron per classificare mnist. 
3. [Field test del MLP](MLP_field_test.ipynb): questo è il vero esercizio della settimana che gli altri due notebook vi preparano ad 
   affrontare. È composto da tre sfide:
   1. addestrare un MLP su [FashionMNIST](https://github.com/zalandoresearch/fashion-mnist): è analogo a MNIST come 
      struttura, ma vi darà un po' più di soddisfazione.
   2. addestrare un MLP su [YearPredictionMSD](https://archive.ics.uci.edu/ml/datasets/YearPredictionMSD): l'idea di 
      questo esercizio è quella di utilizzare una rete neurale per migliorare le performance rispetto alla soluzione 
      che avete già implementato con la logistic regression nell'[esercitazione 6](https://github.com/Sapienza-AI-Lab/esercitazione6-22-23). In questo caso l'aspetto che ci 
      preme esplorare è l'efficacia del MLP nell'imparare una rappresentazione (i.e. delle features) migliore per la 
      classifcazione, o la regressione.
   3. addestrare un MLP su CIFAR-10: riprenderemo questo dataset anche con le reti convoluzionali, ma iniziamo a 
      farci un'idea delle sue caratterisitche addestrando im modello migliore possibile utilizzando un MLP.
