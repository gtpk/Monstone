   M S B A M L   `   `   `  ����D  @LogicTool, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null8*clr-namespace:LogicTool;assembly=LogicTool	LogicTool  5      I EMarxEngineTool, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null/clr-namespace:MarxEngineToolMarxEngineTool 6?   "   MarxEngineTool.PieceProperty   5      R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5      @d2http://schemas.microsoft.com/expression/blend/2008     5      Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5      @	LogicTool*clr-namespace:LogicTool;assembly=LogicTool     5      .localclr-namespace:MarxEngineTool     6?   -   5          >�Name$  UserControl��5	      .��5      � -   5         �Name$ 
LayoutRoot��5      .+�5      �� $��0q�6   $	��Top=�6   $��598.04��6.    � DataContext 5      !   LogicTool.PieceAddViewModel  5      .+�5      �� $��0q�6    �� Orientation$ Vertical=�6   $��598.04��62   $��258.032��6B   .+�5      (� $��0,0,0,5q�6   $��54.54��6    (� Stretch$
 Fill=�6.   .��5      � $��54.54��6   $��258.032��6   .+�5      � $��55,4.367,10,28.133q�6   .+�5   	   �� $��64.167,0,0,0q�6    �� TextWrapping$
 Wrap=�6'   {�.  $��Center=�6M   ��6h   �� *piecemodel.CurrentName+�� 5   	   $
��Left=�6   $
��Wrap=�6.   $
��53.5��6B   $��피스 번호��6O    �� TextAlignment$ Right=�6\   $��0,2.133,0,0q�6r   {�.  ���	#FFC1C1C1$��Center=�6�   5   	   � 5      $��10,10,208.032,4.54q�6   .+�5   	   �� $
��Left=�6   $��40��6.   $	��Top=�6:   $��40��6R   ���	#FF404040$��-2.5,-2.5,0,0q�6n   �� 5   	   $��0,0,5,5q�6   $��1377030668_puzzle.png��6    $
��Fill=�6?   $��35��6N   $��35��6Y   $��Center=�6e   $��Center=�6�   5   	   � 5      $��55,27.96,10,4.54q�6   .+�5   	   �� $
��Left=�6   $
��Wrap=�6.   $��193.032��6B   $��형식 : Piece��6R   $ Center=�6d   $��0,4.106,0,1.973q�6{   {�.  ���	#FFC1C1C1$��Center=�6�   5   	   5       5!      &   MarxEngineTool.SourceTextureView  5#      $	��178��6   $��0q�6+   $��Center=�66   $��Center=�6S   $	��178��6n      TgaImageUri 6z   �� *piecemodel.TextureName+%  MarxEngineTool.AlphaTextureView  5$      $	��178��6   $��0q�6*   $��Center=�65   $��Center=�6R   $	��178��6m      TgaAlphaImageUri 6y   �� *&$Instance.piecemodel.AlphaTextureName+� 5%      $��49.08��6   $
��10,0q�6   .+�5&      � $��0,0,0,27.04q�6   .+�5'      �� $��105.071,0,0,0q�6   $
 Wrap=�6'   {�.  ��6M   �� *piecemodel.Width+�� 5(      $
��Left=�6   $
��Wrap=�6-   $��42.333��6A   $��Width��6P   5)      � 5*      $��0,27.04,0,0q�6   .+�5+      �� $��105.071,0,0,0q�6   $
 Wrap=�6'   {�.  ��6M   �� *piecemodel.Height+�� 5,      $
��Left=�6   $
��Wrap=�6-   $��98��6A   $��Height��6L   5-      5.      �� 5/      $��48��6   $��	10,0,10,5q�6   .+�50      �� $
��Left=�6   $
��Wrap=�6,   $��98��6@   $��Rotation��6K   $��22.04��6[   !  MarxEngineTool.VectorEditer  51      $
��10,0q�6   52      �� 53      $��48��6   $��	10,0,10,5q�6   .+�54      �� $
��Left=�6   $
��Wrap=�6,   $��98��6@   $��
Tranceform��6K   $��22.04��6]     55      $
��10,0q�6    6(   �� *piecemodel.Trance+56      � 57      $��22.04��6   $��	10,0,10,5q�6   .+�58      �� $��105.071,0,0,0q�6   $
 Wrap=�6&   {�.  ��6:   �� *piecemodel.Scale+6\   �� 59      $
��Left=�6   $
��Wrap=�6,   $��98��6@   $��Scale��6K   5:      5<      5=      5>      5?      