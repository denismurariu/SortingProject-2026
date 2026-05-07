import pandas as pd
import plotly.express as px


df = pd.read_csv('rezultate.csv')


fig = px.line(
    df, 
    x="N", 
    y="TimpSec", 
    color="Algoritm", 
    facet_col="TipDate",       
    markers=True,
    title="Analiza Complexității Algoritmilor de Sortare",
    labels={"N": "Nr. Elemente (N)", "TimpSec": "Timp Execuție (secunde)"},
    hover_data=["TipDate"]     
)


fig.update_layout(
    hovermode="x unified",    
    template="plotly_dark",    
    legend_title_text='Algoritmi',
    dragmode="zoom"            
)

fig.show()