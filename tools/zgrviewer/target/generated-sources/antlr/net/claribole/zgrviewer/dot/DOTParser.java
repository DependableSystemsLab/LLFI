// $ANTLR 2.7.7 (20060906): "DOT.g" -> "DOTParser.java"$

package net.claribole.zgrviewer.dot;

import java.io.StringReader;
import antlr.CommonAST;
import antlr.debug.misc.ASTFrame;

import antlr.TokenBuffer;
import antlr.TokenStreamException;
import antlr.TokenStreamIOException;
import antlr.ANTLRException;
import antlr.LLkParser;
import antlr.Token;
import antlr.TokenStream;
import antlr.RecognitionException;
import antlr.NoViableAltException;
import antlr.MismatchedTokenException;
import antlr.SemanticException;
import antlr.ParserSharedInputState;
import antlr.collections.impl.BitSet;
import antlr.collections.AST;
import java.util.Hashtable;
import antlr.ASTFactory;
import antlr.ASTPair;
import antlr.collections.impl.ASTArray;

/**
 * Parser for GraphViz Dot files. This parser can generate an AST to be walked
 * later.
 * @author Eric Mounhem
 */
public class DOTParser extends antlr.LLkParser       implements DOTTokenTypes
 {

protected DOTParser(TokenBuffer tokenBuf, int k) {
  super(tokenBuf,k);
  tokenNames = _tokenNames;
  buildTokenTypeASTClassMap();
  astFactory = new ASTFactory(getTokenTypeToASTClassMap());
}

public DOTParser(TokenBuffer tokenBuf) {
  this(tokenBuf,2);
}

protected DOTParser(TokenStream lexer, int k) {
  super(lexer,k);
  tokenNames = _tokenNames;
  buildTokenTypeASTClassMap();
  astFactory = new ASTFactory(getTokenTypeToASTClassMap());
}

public DOTParser(TokenStream lexer) {
  this(lexer,2);
}

public DOTParser(ParserSharedInputState state) {
  super(state,2);
  tokenNames = _tokenNames;
  buildTokenTypeASTClassMap();
  astFactory = new ASTFactory(getTokenTypeToASTClassMap());
}

	public final void graph() throws RecognitionException, TokenStreamException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST graph_AST = null;
		
		try {      // for error handling
			{
			switch ( LA(1)) {
			case STRICT:
			{
				match(STRICT);
				break;
			}
			case GRAPH:
			case DIGRAPH:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
			{
			switch ( LA(1)) {
			case DIGRAPH:
			{
				AST tmp35_AST = null;
				tmp35_AST = astFactory.create(LT(1));
				astFactory.makeASTRoot(currentAST, tmp35_AST);
				match(DIGRAPH);
				break;
			}
			case GRAPH:
			{
				AST tmp36_AST = null;
				tmp36_AST = astFactory.create(LT(1));
				astFactory.makeASTRoot(currentAST, tmp36_AST);
				match(GRAPH);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
			AST tmp37_AST = null;
			tmp37_AST = astFactory.create(LT(1));
			astFactory.addASTChild(currentAST, tmp37_AST);
			match(ID);
			stmt_list();
			astFactory.addASTChild(currentAST, returnAST);
			graph_AST = (AST)currentAST.root;
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_0);
		}
		returnAST = graph_AST;
	}
	
	public final void stmt_list() throws RecognitionException, TokenStreamException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST stmt_list_AST = null;
		
		try {      // for error handling
			AST tmp38_AST = null;
			tmp38_AST = astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp38_AST);
			match(LCUR);
			{
			_loop7:
			do {
				if ((_tokenSet_1.member(LA(1)))) {
					stmt();
					astFactory.addASTChild(currentAST, returnAST);
					{
					switch ( LA(1)) {
					case SEMI:
					{
						match(SEMI);
						break;
					}
					case GRAPH:
					case SUBGRAPH:
					case NODE:
					case EDGE:
					case LABEL:
					case ID:
					case LCUR:
					case RCUR:
					{
						break;
					}
					default:
					{
						throw new NoViableAltException(LT(1), getFilename());
					}
					}
					}
				}
				else {
					break _loop7;
				}
				
			} while (true);
			}
			match(RCUR);
			stmt_list_AST = (AST)currentAST.root;
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_2);
		}
		returnAST = stmt_list_AST;
	}
	
	public final void stmt() throws RecognitionException, TokenStreamException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST stmt_AST = null;
		
		try {      // for error handling
			switch ( LA(1)) {
			case GRAPH:
			case NODE:
			case EDGE:
			{
				attr_stmt();
				astFactory.addASTChild(currentAST, returnAST);
				stmt_AST = (AST)currentAST.root;
				break;
			}
			case LABEL:
			{
				AST tmp41_AST = null;
				tmp41_AST = astFactory.create(LT(1));
				astFactory.makeASTRoot(currentAST, tmp41_AST);
				match(LABEL);
				match(EQUAL);
				{
				switch ( LA(1)) {
				case ID:
				{
					AST tmp43_AST = null;
					tmp43_AST = astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp43_AST);
					match(ID);
					break;
				}
				case HTML:
				{
					AST tmp44_AST = null;
					tmp44_AST = astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp44_AST);
					match(HTML);
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				}
				}
				stmt_AST = (AST)currentAST.root;
				break;
			}
			default:
				if ((LA(1)==SUBGRAPH||LA(1)==ID||LA(1)==LCUR) && (_tokenSet_3.member(LA(2)))) {
					node_edge_subgraph_stmt();
					astFactory.addASTChild(currentAST, returnAST);
					stmt_AST = (AST)currentAST.root;
				}
				else if ((LA(1)==ID) && (LA(2)==EQUAL)) {
					AST tmp45_AST = null;
					tmp45_AST = astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp45_AST);
					match(ID);
					AST tmp46_AST = null;
					tmp46_AST = astFactory.create(LT(1));
					astFactory.makeASTRoot(currentAST, tmp46_AST);
					match(EQUAL);
					AST tmp47_AST = null;
					tmp47_AST = astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp47_AST);
					match(ID);
					stmt_AST = (AST)currentAST.root;
				}
			else {
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_4);
		}
		returnAST = stmt_AST;
	}
	
	public final void node_edge_subgraph_stmt() throws RecognitionException, TokenStreamException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST node_edge_subgraph_stmt_AST = null;
		
		try {      // for error handling
			{
			switch ( LA(1)) {
			case ID:
			{
				node_id();
				astFactory.addASTChild(currentAST, returnAST);
				break;
			}
			case SUBGRAPH:
			case LCUR:
			{
				subgraph();
				astFactory.addASTChild(currentAST, returnAST);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
			{
			switch ( LA(1)) {
			case GRAPH:
			case SUBGRAPH:
			case NODE:
			case EDGE:
			case LABEL:
			case ID:
			case LCUR:
			case SEMI:
			case RCUR:
			case LBR:
			{
				{
				_loop27:
				do {
					if ((LA(1)==LBR)) {
						AST tmp48_AST = null;
						tmp48_AST = astFactory.create(LT(1));
						astFactory.makeASTRoot(currentAST, tmp48_AST);
						match(LBR);
						a_list();
						astFactory.addASTChild(currentAST, returnAST);
						match(RBR);
					}
					else {
						break _loop27;
					}
					
				} while (true);
				}
				break;
			}
			case D_EDGE_OP:
			case ND_EDGE_OP:
			{
				{
				int _cnt31=0;
				_loop31:
				do {
					if ((LA(1)==D_EDGE_OP||LA(1)==ND_EDGE_OP)) {
						{
						switch ( LA(1)) {
						case D_EDGE_OP:
						{
							AST tmp50_AST = null;
							tmp50_AST = astFactory.create(LT(1));
							astFactory.makeASTRoot(currentAST, tmp50_AST);
							match(D_EDGE_OP);
							break;
						}
						case ND_EDGE_OP:
						{
							AST tmp51_AST = null;
							tmp51_AST = astFactory.create(LT(1));
							astFactory.makeASTRoot(currentAST, tmp51_AST);
							match(ND_EDGE_OP);
							break;
						}
						default:
						{
							throw new NoViableAltException(LT(1), getFilename());
						}
						}
						}
						{
						switch ( LA(1)) {
						case ID:
						{
							node_id();
							astFactory.addASTChild(currentAST, returnAST);
							break;
						}
						case SUBGRAPH:
						case LCUR:
						{
							subgraph();
							astFactory.addASTChild(currentAST, returnAST);
							break;
						}
						default:
						{
							throw new NoViableAltException(LT(1), getFilename());
						}
						}
						}
					}
					else {
						if ( _cnt31>=1 ) { break _loop31; } else {throw new NoViableAltException(LT(1), getFilename());}
					}
					
					_cnt31++;
				} while (true);
				}
				{
				_loop33:
				do {
					if ((LA(1)==LBR)) {
						sing_attr_list();
						astFactory.addASTChild(currentAST, returnAST);
					}
					else {
						break _loop33;
					}
					
				} while (true);
				}
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
			node_edge_subgraph_stmt_AST = (AST)currentAST.root;
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_4);
		}
		returnAST = node_edge_subgraph_stmt_AST;
	}
	
	public final void attr_stmt() throws RecognitionException, TokenStreamException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST attr_stmt_AST = null;
		
		try {      // for error handling
			{
			switch ( LA(1)) {
			case GRAPH:
			{
				AST tmp52_AST = null;
				tmp52_AST = astFactory.create(LT(1));
				astFactory.makeASTRoot(currentAST, tmp52_AST);
				match(GRAPH);
				break;
			}
			case NODE:
			{
				AST tmp53_AST = null;
				tmp53_AST = astFactory.create(LT(1));
				astFactory.makeASTRoot(currentAST, tmp53_AST);
				match(NODE);
				break;
			}
			case EDGE:
			{
				AST tmp54_AST = null;
				tmp54_AST = astFactory.create(LT(1));
				astFactory.makeASTRoot(currentAST, tmp54_AST);
				match(EDGE);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
			attr_list();
			astFactory.addASTChild(currentAST, returnAST);
			attr_stmt_AST = (AST)currentAST.root;
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_4);
		}
		returnAST = attr_stmt_AST;
	}
	
	public final void attr_list() throws RecognitionException, TokenStreamException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST attr_list_AST = null;
		
		try {      // for error handling
			{
			int _cnt14=0;
			_loop14:
			do {
				if ((LA(1)==LBR)) {
					AST tmp55_AST = null;
					tmp55_AST = astFactory.create(LT(1));
					astFactory.makeASTRoot(currentAST, tmp55_AST);
					match(LBR);
					a_list();
					astFactory.addASTChild(currentAST, returnAST);
					match(RBR);
				}
				else {
					if ( _cnt14>=1 ) { break _loop14; } else {throw new NoViableAltException(LT(1), getFilename());}
				}
				
				_cnt14++;
			} while (true);
			}
			attr_list_AST = (AST)currentAST.root;
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_4);
		}
		returnAST = attr_list_AST;
	}
	
	public final void a_list() throws RecognitionException, TokenStreamException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST a_list_AST = null;
		
		try {      // for error handling
			{
			_loop17:
			do {
				if ((LA(1)==LABEL||LA(1)==ID)) {
					a_list_elts();
					astFactory.addASTChild(currentAST, returnAST);
				}
				else {
					break _loop17;
				}
				
			} while (true);
			}
			a_list_AST = (AST)currentAST.root;
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		}
		returnAST = a_list_AST;
	}
	
	public final void a_list_elts() throws RecognitionException, TokenStreamException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST a_list_elts_AST = null;
		
		try {      // for error handling
			{
			switch ( LA(1)) {
			case ID:
			{
				AST tmp57_AST = null;
				tmp57_AST = astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp57_AST);
				match(ID);
				{
				switch ( LA(1)) {
				case EQUAL:
				{
					AST tmp58_AST = null;
					tmp58_AST = astFactory.create(LT(1));
					astFactory.makeASTRoot(currentAST, tmp58_AST);
					match(EQUAL);
					AST tmp59_AST = null;
					tmp59_AST = astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp59_AST);
					match(ID);
					break;
				}
				case LABEL:
				case ID:
				case RBR:
				case COMMA:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				}
				}
				break;
			}
			case LABEL:
			{
				AST tmp60_AST = null;
				tmp60_AST = astFactory.create(LT(1));
				astFactory.makeASTRoot(currentAST, tmp60_AST);
				match(LABEL);
				match(EQUAL);
				{
				switch ( LA(1)) {
				case ID:
				{
					AST tmp62_AST = null;
					tmp62_AST = astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp62_AST);
					match(ID);
					break;
				}
				case HTML:
				{
					AST tmp63_AST = null;
					tmp63_AST = astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp63_AST);
					match(HTML);
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				}
				}
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
			{
			switch ( LA(1)) {
			case COMMA:
			{
				match(COMMA);
				break;
			}
			case LABEL:
			case ID:
			case RBR:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
			a_list_elts_AST = (AST)currentAST.root;
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_6);
		}
		returnAST = a_list_elts_AST;
	}
	
	public final void node_id() throws RecognitionException, TokenStreamException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST node_id_AST = null;
		
		try {      // for error handling
			AST tmp65_AST = null;
			tmp65_AST = astFactory.create(LT(1));
			astFactory.addASTChild(currentAST, tmp65_AST);
			match(ID);
			{
			switch ( LA(1)) {
			case COLON:
			{
				AST tmp66_AST = null;
				tmp66_AST = astFactory.create(LT(1));
				astFactory.makeASTRoot(currentAST, tmp66_AST);
				match(COLON);
				AST tmp67_AST = null;
				tmp67_AST = astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp67_AST);
				match(ID);
				{
				switch ( LA(1)) {
				case COLON:
				{
					compass();
					astFactory.addASTChild(currentAST, returnAST);
					break;
				}
				case GRAPH:
				case SUBGRAPH:
				case NODE:
				case EDGE:
				case LABEL:
				case ID:
				case LCUR:
				case SEMI:
				case RCUR:
				case LBR:
				case D_EDGE_OP:
				case ND_EDGE_OP:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				}
				}
				break;
			}
			case GRAPH:
			case SUBGRAPH:
			case NODE:
			case EDGE:
			case LABEL:
			case ID:
			case LCUR:
			case SEMI:
			case RCUR:
			case LBR:
			case D_EDGE_OP:
			case ND_EDGE_OP:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
			node_id_AST = (AST)currentAST.root;
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		}
		returnAST = node_id_AST;
	}
	
	public final void subgraph() throws RecognitionException, TokenStreamException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST subgraph_AST = null;
		
		try {      // for error handling
			switch ( LA(1)) {
			case SUBGRAPH:
			{
				AST tmp68_AST = null;
				tmp68_AST = astFactory.create(LT(1));
				astFactory.makeASTRoot(currentAST, tmp68_AST);
				match(SUBGRAPH);
				{
				switch ( LA(1)) {
				case ID:
				{
					AST tmp69_AST = null;
					tmp69_AST = astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp69_AST);
					match(ID);
					{
					if ((LA(1)==LCUR) && (_tokenSet_8.member(LA(2)))) {
						stmt_list();
						astFactory.addASTChild(currentAST, returnAST);
					}
					else if ((_tokenSet_7.member(LA(1))) && (_tokenSet_9.member(LA(2)))) {
					}
					else {
						throw new NoViableAltException(LT(1), getFilename());
					}
					
					}
					break;
				}
				case LCUR:
				{
					stmt_list();
					astFactory.addASTChild(currentAST, returnAST);
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				}
				}
				subgraph_AST = (AST)currentAST.root;
				break;
			}
			case LCUR:
			{
				stmt_list();
				astFactory.addASTChild(currentAST, returnAST);
				subgraph_AST = (AST)currentAST.root;
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		}
		returnAST = subgraph_AST;
	}
	
	public final void sing_attr_list() throws RecognitionException, TokenStreamException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST sing_attr_list_AST = null;
		
		try {      // for error handling
			AST tmp70_AST = null;
			tmp70_AST = astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp70_AST);
			match(LBR);
			a_list();
			astFactory.addASTChild(currentAST, returnAST);
			match(RBR);
			sing_attr_list_AST = (AST)currentAST.root;
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_10);
		}
		returnAST = sing_attr_list_AST;
	}
	
	public final void compass() throws RecognitionException, TokenStreamException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST compass_AST = null;
		
		try {      // for error handling
			AST tmp72_AST = null;
			tmp72_AST = astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp72_AST);
			match(COLON);
			AST tmp73_AST = null;
			tmp73_AST = astFactory.create(LT(1));
			astFactory.addASTChild(currentAST, tmp73_AST);
			match(ID);
			compass_AST = (AST)currentAST.root;
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		}
		returnAST = compass_AST;
	}
	
	
	public static final String[] _tokenNames = {
		"<0>",
		"EOF",
		"<2>",
		"NULL_TREE_LOOKAHEAD",
		"\"graph\"",
		"\"digraph\"",
		"\"subgraph\"",
		"\"node\"",
		"\"edge\"",
		"\"strict\"",
		"\"label\"",
		"an identifier",
		"LCUR",
		"SEMI",
		"RCUR",
		"EQUAL",
		"HTML",
		"LBR",
		"RBR",
		"COMMA",
		"D_EDGE_OP",
		"ND_EDGE_OP",
		"COLON",
		"WS",
		"CMT",
		"CPP_COMMENT",
		"ESC",
		"LT",
		"GT"
	};
	
	protected void buildTokenTypeASTClassMap() {
		tokenTypeToASTClassMap=null;
	};
	
	private static final long[] mk_tokenSet_0() {
		long[] data = { 2L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_0 = new BitSet(mk_tokenSet_0());
	private static final long[] mk_tokenSet_1() {
		long[] data = { 7632L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_1 = new BitSet(mk_tokenSet_1());
	private static final long[] mk_tokenSet_2() {
		long[] data = { 3309010L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_2 = new BitSet(mk_tokenSet_2());
	private static final long[] mk_tokenSet_3() {
		long[] data = { 7503312L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_3 = new BitSet(mk_tokenSet_3());
	private static final long[] mk_tokenSet_4() {
		long[] data = { 32208L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_4 = new BitSet(mk_tokenSet_4());
	private static final long[] mk_tokenSet_5() {
		long[] data = { 262144L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_5 = new BitSet(mk_tokenSet_5());
	private static final long[] mk_tokenSet_6() {
		long[] data = { 265216L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_6 = new BitSet(mk_tokenSet_6());
	private static final long[] mk_tokenSet_7() {
		long[] data = { 3309008L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_7 = new BitSet(mk_tokenSet_7());
	private static final long[] mk_tokenSet_8() {
		long[] data = { 24016L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_8 = new BitSet(mk_tokenSet_8());
	private static final long[] mk_tokenSet_9() {
		long[] data = { 7798226L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_9 = new BitSet(mk_tokenSet_9());
	private static final long[] mk_tokenSet_10() {
		long[] data = { 163280L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_10 = new BitSet(mk_tokenSet_10());
	
	}
